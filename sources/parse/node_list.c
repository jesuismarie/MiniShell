/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:59:16 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/09 14:59:17 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_ast_node	*last_node(t_ast_node *node_list)
{
	if (node_list)
		while (node_list)
			node_list = node_list->next;
	return (node_list);
}

void	node_push(t_ast_node **node_list, t_ast_node *to_push)
{
	if (*node_list)
		last_node(*node_list)->next = to_push;
	else
		*node_list = to_push;
}
