/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:48:22 by mnazarya          #+#    #+#             */
/*   Updated: 2023/09/29 21:06:01 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quote_check(char *line, int *i)
{
	int	quote;

	if (line[*i] == SQUOTES || line[*i] == DQUOTES)
	{
		quote = line[*i];
		(*i)++;
		while (line && line[*i] && line[*i] != quote)
			(*i)++;
	}
}

static void	print_quote_error(char *line, int *i, char quote)
{
	quote_check(line, i);
	if (line && !line[*i])
	{
		if (quote == SQUOTES)
			ft_putstr_fd(SQUOTES_ERR, 2);
		else
			ft_putstr_fd(DQUOTES_ERR, 2);
		g_stat = -1;
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

void	check_open_close(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == SQUOTES)
			print_quote_error(line, &i, SQUOTES);
		else if (line[i] == DQUOTES)
			print_quote_error(line, &i, DQUOTES);
		i++;
		if (g_stat == -1)
			return ;
	}
	check_brace(line);
}
