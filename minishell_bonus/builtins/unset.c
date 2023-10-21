/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:33:41 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/27 18:38:19 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok	*find_unset_args(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp && ft_strncmp(temp->var, "unset", 6) != 0)
		temp = temp->next;
	temp = temp->next;
	return (temp);
}

t_node	*find_node_to_remove(char *var_before_equal, t_chained *lst)
{
	t_node	*temp;	

	temp = lst->start;
	while (temp)
	{
		if (ft_strncmp(var_before_equal, temp->variable,
				ft_strlenequal(temp->variable)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

int	valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg[i] || !ft_isalpha(arg[i]))
		return (FALSE);
	return (TRUE);
}

void	norm_unset(t_unset *uns, t_shell *shell)
{
	uns->env_node = find_node_to_remove(uns->var, shell->env_l);
	remove_current_node(uns->env_node, shell->env_l);
}

int	unset_variable(t_shell *shell)
{
	t_unset	*uns;

	uns = malloc(sizeof(t_unset));
	if (!uns)
		return (EXIT_FAILURE);
	uns->temp = find_unset_args(shell);
	uns->env_node = shell->env_l->start;
	while (uns->temp)
	{
		uns->var = ft_strndup(uns->temp->var, 0, ft_strlen(uns->temp->var));
		if (!valid_arg(uns->var))
			printf("unset: '%s': not a valid identifier\n", uns->temp->var);
		else if (envchecker(uns->var, shell->sorted_env_l))
		{
			uns->export_node = find_node_to_remove(uns->var,
					shell->sorted_env_l);
			remove_current_node(uns->export_node, shell->sorted_env_l);
		}
		if (envchecker(uns->var, shell->env_l))
			norm_unset(uns, shell);
		free(uns->var);
		uns->temp = uns->temp->next;
	}
	free(uns);
	return (EXIT_SUCCESS);
}
