/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:48:22 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/29 06:25:59 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quote_check(char *line, int *i)
{
	int	quote;

	if (line && line[*i] && (line[*i] == SQUOTES || line[*i] == DQUOTES))
	{
		quote = line[*i];
		(*i)++;
		while (line && line[*i] && line[*i] != quote)
			(*i)++;
	}
}

static void	print_quote_error(t_shell *shell, int *i, char quote)
{
	quote_check(shell->line, i);
	if (shell->line && !shell->line[*i])
	{
		if (quote == SQUOTES)
			set_err(shell, SQUOTES_ERR);
		else
			set_err(shell, DQUOTES_ERR);
		g_stat = -2;
	}
}

void	clear_stack(t_stack **brace)
{
	t_stack *tmp;

	while (*brace)
	{
		tmp = (*brace)->next;
		free(*brace);
		*brace = tmp;
	}
}

void	check_open_close(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->line && shell->line[i])
	{
		if (shell->line[i] == SQUOTES)
			print_quote_error(shell, &i, SQUOTES);
		else if (shell->line[i] == DQUOTES)
			print_quote_error(shell, &i, DQUOTES);
		else
			i++;
		if (g_stat == -1)
			return ;
	}
	check_brace(shell);
}
