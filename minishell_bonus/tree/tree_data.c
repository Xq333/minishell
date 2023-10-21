/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:32:25 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/10 08:50:17 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_and_or(char *str)
{
	if (ft_strncmp(str, "&&", 3) == 0
		|| ft_strncmp(str, "||", 3) == 0)
		return (1);
	return (0);
}

int	is_operator(char *str)
{
	if (ft_strncmp(str, "&&", 3) == 0
		|| ft_strncmp(str, "||", 3) == 0
		|| ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}

int	and_or_in_cmd(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (is_and_or(temp->var) && temp->quote == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	operator_in_cmd(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (is_operator(temp->var) && temp->quote == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}
