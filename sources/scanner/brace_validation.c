/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:29:05 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/29 01:37:21 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_stack	*new_node(char c)
{
	t_stack	*node;

	node = ft_calloc(sizeof(t_stack), 1);
	error_exit(!node, "malloc", 12);
	node->c = c;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	stack_push(t_stack **brace, char c)
{
	t_stack	*tmp;

	if (!(*brace))
		*brace = new_node(c);
	else
	{
		tmp = *brace;
		*brace = new_node(c);
		tmp->prev = *brace;
		(*brace)->next = tmp;
	}
}

static void	stack_pop(t_stack **brace)
{
	t_stack	*tmp;

	if (!(*brace))
		return ;
	tmp = *brace;
	*brace = (*brace)->next;
	if ((*brace))
		(*brace)->prev = NULL;
	tmp->next = NULL;
	free(tmp);
	tmp = NULL;
}

static void	brace_validation(t_shell *shell, t_stack *brace)
{
	if (brace)
	{
		set_err(shell, ERR_OP_B);
		g_stat = -2;
		clear_stack(&brace);
		return ;
	}
}

void	check_brace(t_shell *shell)
{
	t_stack	*brace;
	int		i;

	i = 0;
	brace = NULL;
	while (shell->line[i])
	{
		quote_check(shell->line, &i);
		if (shell->line[i] && shell->line[i] == '(')
			stack_push(&brace, shell->line[i]);
		else if (shell->line[i] && shell->line[i] == ')')
		{
			if (!brace)
			{
				shell->err = 1;
				g_stat = -2;
				return set_err(shell, ERR_CL_B), clear_stack(&brace);
			}
			else
				stack_pop(&brace);
		}
		if (shell->line[i])
			i++;
	}
	brace_validation(shell, brace);
}
