/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:59:41 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/09 14:59:42 by mnazarya         ###   ########.fr       */
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
	(void)shell;
	if (!tok_lst)
		return (NULL);
	// tree = parse_pipeline(shell, tok_lst);
	return (tree);
}
