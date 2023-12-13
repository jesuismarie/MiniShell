/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 03:31:24 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/11 09:18:00 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast_node	*parse_cmd(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*node;

	if ((*tok_lst) && ((*tok_lst)->type == HEREDOC \
	|| (*tok_lst)->type == APPEND || (*tok_lst)->type == FILE_IN \
	|| (*tok_lst)->type == FILE_OUT))
		node = parse_redir(shell, tok_lst);
	else if ((*tok_lst)->type == BRACE_OPEN)
		node = parse_subshell(shell, tok_lst);
	// else if (*tok_lst)
	return (node);
}

t_ast_node	*parse_subshell(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*node;

	node = NULL;
	*tok_lst = (*tok_lst)->next;
	node = line_parsing(shell, tok_lst);
	node->subshell_flag = 1;
	return (node);
}
