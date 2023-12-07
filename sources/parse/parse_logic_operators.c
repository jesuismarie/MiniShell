/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logic_operators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:33:25 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/07 17:04:50 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast_node	*parse_logic_op(t_shell *shell, t_ast_node *left, t_token **scan)
{
	t_ast_node	*node;
	t_operator	*op;

	node = ft_calloc(sizeof(t_ast_node), 1);
	error_exit(!node, "malloc", 12);
	op = ft_calloc(sizeof(t_operator), 1);
	error_exit(!op, "malloc", 12);
	if ((*scan)->type == AND_OP || (*scan)->type == OR_OP)
	{
		node->type = AST_LOGICAL_OP;
		op->left = left;
		op->right = parse_pipeline(shell, scan);
		op->type = (*scan)->type;
		node->node = (void *)op;
		node->subshell_flag = 0;
		node->next = NULL;
		node->prev = NULL;
		return (parse_logic_op(shell, node, scan));
	}
	return (left);
}
