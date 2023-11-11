/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:10:22 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/11 17:30:30 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast_node	*new_word_node(t_token **tok_lst)
{
	t_ast_node	*node;
	t_input		*word;

	node = ft_calloc(sizeof(t_ast_node), 1);
	error_exit(!node, "malloc", 12);
	node->type = AST_WORD;
	word = ft_calloc(sizeof(t_input), 1);
	error_exit(!word, "malloc", 12);
	if ((*tok_lst) && (*tok_lst)->cmd && (*tok_lst)->cmd->input)
		word->input = ft_strdup((*tok_lst)->cmd->input);
	else
		word->input = ft_strdup("");
	word->flag = (*tok_lst)->cmd->flag;
	node->node = word;
	node->next = NULL;
	node->prev = NULL;
	node->err_mss = NULL;
	return (node);
}
