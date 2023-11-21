/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:06:24 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/11 17:10:27 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast_node	*parse_cmd(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*node;

	node = NULL;
	if ((*tok_lst)->type == BRACE_OPEN)
	{
		*tok_lst = (*tok_lst)->next;
		node = line_parsing(shell, tok_lst);
		node->subshell_flag = 1;
	}
	else if ((*tok_lst)->type == BRACE_CLOSE)
		*tok_lst = (*tok_lst)->next;
	// else if ((*tok_lst)->type == WORD)
	// 	node = parse_word(*tok_lst, shell);
	return (node);
}

t_ast_node	*parse_pipeline(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*node;

	if (shell->err != 0)
		exit(1); //
	node = parse_cmd(shell, tok_lst);
	return (node);
}
