/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:36:36 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/11 14:51:32 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_redirection_parsing(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp && is_infile_redirection(shell->user_command))
	{
		if (ft_strncmp(temp->var, "<", 2) == 0 && temp->quote == 0)
		{
			if (!temp->next)
				return (printf("Redirection needs a file\n"));
			if (infile_redirection(shell, temp) != 0)
				return (EXIT_FAILURE);
			temp = shell->user_command->start;
		}
		else if (ft_strncmp(temp->var, "<<", 3) == 0 && temp->quote == 0)
		{
			if (!temp->next)
				return (printf("Heredoc needs a delimiter\n"));
			if (heredoc_redirection(shell, temp) != 0)
				return (EXIT_FAILURE);
			temp = shell->user_command->start;
		}
		else
			temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	outfile_redirection_parsing(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp && is_outfile_redirection(shell->user_command))
	{
		if (ft_strncmp(temp->var, ">", 2) == 0 && temp->quote == 0)
		{
			if (!temp->next)
				return (printf("Redirection needs a file\n"));
			if (outfile_redirection(shell, temp) != 0)
				return (EXIT_FAILURE);
			temp = shell->user_command->start;
		}
		else if (ft_strncmp(temp->var, ">>", 3) == 0 && temp->quote == 0)
		{
			if (!temp->next)
				return (printf("Append needs a file\n"));
			if (append_redirection(shell, temp) != 0)
				return (EXIT_FAILURE);
			temp = shell->user_command->start;
		}
		else
			temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
