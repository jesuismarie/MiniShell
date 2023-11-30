/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:29:05 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/30 17:03:16 by mnazarya         ###   ########.fr       */
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

static void	brace_validation(t_shell *shell, t_stack *brace, t_token **tok_lst)
{
	t_token	*t;

	if (brace)
	{
		t = *tok_lst;
		while (t)
		{
			if (t->type == BRACE_OPEN)
			{
				t->err = 1;
				break ;
			}
			t = t->next;
		}
		g_stat = -2;
		return (set_err(shell, ERR_OP_B), clear_stack(&brace));
	}
}

void	check_brace(t_shell *shell, t_token **tok_lst)
{
	t_stack	*brace;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *tok_lst;
	brace = NULL;
	while (tmp)
	{
		if (tmp && tmp->type == BRACE_OPEN)
			stack_push(&brace, LBRACE);
		else if (tmp && tmp->type == BRACE_CLOSE)
		{
			if (!brace)
			{
				tmp->err = 1;
				g_stat = -2;
				return (set_err(shell, ERR_CL_B), clear_stack(&brace));
			}
			else
				stack_pop(&brace);
		}
		tmp = tmp->next;
	}
	brace_validation(shell, brace, tok_lst);
}
