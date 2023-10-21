/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:11:29 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/11 18:28:47 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_branch	*clean(t_branch *temp, t_branch *map)
{
	t_branch	*temp2;

	temp2 = NULL;
	if (temp && temp->left)
		return (clean(temp->left, map));
	else if (temp && temp->right)
		return (clean(temp->right, map));
	else if (temp && temp->dad)
	{	
		temp2 = temp->dad;
		clean_node(temp);
		if (temp2 == map)
			return (EXIT_SUCCESS);
		return (clean(temp2, map));
	}
	return (temp);
}

void	clean_node(t_branch *temp)
{
	if (temp && temp->cmd && *temp->cmd)
		free_array(temp->cmd);
	else if (temp && temp->cmd)
		free(temp->cmd);
	temp->left_command = NULL;
	temp->right_command = NULL;
	if (temp->cmd_block > 0)
	{
		clear_toklst(temp->subshell);
		free(temp->subshell);
	}
	temp->left = NULL;
	temp->right = NULL;
	temp->subshell = NULL;
	if (temp && temp->dad && temp->dad->left)
	{
		free(temp->dad->left);
		temp->dad->left = NULL;
	}
	else if (temp && temp->dad && temp->dad->right)
	{
		free(temp->dad->right);
		temp->dad->right = NULL;
	}
}

int	is_parenthese(char *str)
{
	if (ft_strncmp(str, "(", 2) == 0 || ft_strncmp(str, ")", 2) == 0)
		return (1);
	return (0);
}

void	allocate_pids_and_fds(t_shell *shell, int count)
{
	int	i;

	shell->fd = malloc(sizeof(int *) * shell->nb_of_fds_to_malloc);
	if (!shell->fd)
		return ;
	i = -1;
	while (++i < shell->nb_of_fds_to_malloc)
	{
		shell->fd[i] = malloc(sizeof(int) * 2);
		if (!shell->fd[i])
			return ;
	}
	shell->pid = malloc(sizeof(pid_t) * count);
	if (!shell->pid)
		return ;
	i = -1;
	while (++i < count)
		shell->pid[i] = -1;
}

int	get_bcmd(t_toklst *user_command, t_shell *shell)
{
	t_tok	*temp;
	int		count;

	temp = user_command->start;
	count = 0;
	while (temp)
	{
		if (temp && is_parenthese(temp->var))
			temp = temp->next;
		else if (temp && is_operator(temp->var))
		{
			if (ft_strncmp(temp->var, "|", 2) == 0)
				shell->nb_of_fds_to_malloc++;
			temp = temp->next;
		}
		else
		{
			count++;
			while (temp && !(is_operator(temp->var)
					|| is_parenthese(temp->var)))
				temp = temp->next;
		}
	}
	allocate_pids_and_fds(shell, count);
	return (count);
}
