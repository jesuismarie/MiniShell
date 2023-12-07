/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:28:10 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/07 20:47:54 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_consume(t_token **scanner)
{
	t_token	*node;

	node = *scanner;
	*scanner = (*scanner)->next;
	if (*scanner)
		(*scanner)->prev = NULL;
	free(node->cmd->input);
	free(node->cmd);
	free(node);
}

t_ast_node	*line_parsing(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*tree;

	tree = NULL;
	if (!tok_lst)
		return (NULL);
	tree = parse_pipeline(shell, tok_lst);
	return (parse_logic_op(shell, tree, tok_lst));
}
