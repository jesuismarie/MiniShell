/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:29:05 by mnazarya          #+#    #+#             */
/*   Updated: 2023/09/29 21:02:20 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_stack	*new_node(char c)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
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

static void	brace_validation(t_stack *brace)
{
	if (brace)
	{
		ft_putstr_fd(ERR_MSG, 2);
		ft_putendl_fd("(\'", 2);
		g_stat = -1;
		return ;
	}
}

void	check_brace(char *line)
{
	t_stack	*brace;
	int		i;

	i = 0;
	brace = NULL;
	while (line[i])
	{
		quote_check(line, &i);
		if (line[i] == '(')
			stack_push(&brace, line[i]);
		else if (line[i] == ')')
		{
			if (!brace)
			{
				ft_putstr_fd(ERR_MSG, 2);
				ft_putendl_fd(")\'", 2);
				g_stat = -1;
				return ;
			}
			else
				stack_pop(&brace);
		}
		i++;
	}
	brace_validation(brace);
}
