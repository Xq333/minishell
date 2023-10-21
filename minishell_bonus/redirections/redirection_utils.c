/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:31:06 by eleleux           #+#    #+#             */
/*   Updated: 2023/03/11 18:45:45 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_infile_redirection(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if ((ft_strncmp(temp->var, "<", 2) == 0)
			|| (ft_strncmp(temp->var, "<<", 3) == 0))
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

int	is_outfile_redirection(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if ((ft_strncmp(temp->var, ">", 2) == 0)
			|| (ft_strncmp(temp->var, ">>", 3) == 0))
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

int	delete_operator_and_infile(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	if (shell->user_command->nb_elem == 0)
		return (EXIT_SUCCESS);
	while (temp)
	{
		if ((!ft_strncmp(temp->var, "<", 2)
				|| (!ft_strncmp(temp->var, "<<", 2))))
		{
			remove_current_tok(temp->next, shell->user_command);
			remove_current_tok(temp, shell->user_command);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_FAILURE);
}

int	delete_operator_and_outfile(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	if (shell->user_command->nb_elem == 0)
		return (EXIT_SUCCESS);
	while (temp)
	{
		if ((!ft_strncmp(temp->var, ">", 2)
				|| (!ft_strncmp(temp->var, ">>", 2))))
		{
			remove_current_tok(temp->next, shell->user_command);
			remove_current_tok(temp, shell->user_command);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_FAILURE);
}

char	*append_newline(char *limiter)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (ft_strlen(limiter) + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (limiter[i])
	{
		result[i] = limiter[i];
		i++;
	}
	result[i] = '\n';
	result[i + 1] = '\0';
	return (result);
}
