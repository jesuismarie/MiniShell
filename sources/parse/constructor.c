/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:10:22 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/26 07:11:00 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir	*new_redir_node(t_shell *shell, t_token **tok_lst)
{
	t_redir		*node;

	node = ft_calloc(sizeof(t_redir), 1);
	error_exit(!node, "malloc", 12);
	node->type = (*tok_lst)->type;
	*tok_lst = (*tok_lst)->next;
	node->filename = new_word_node(tok_lst);
	if (node->type == HEREDOC)
		node->fd = parse_heredoc(shell, node->filename);
	return (node);
}

t_input	*new_word_node(t_token **tok_lst)
{
	t_input		*word;

	word = ft_calloc(sizeof(t_input), 1);
	error_exit(!word, "malloc", 12);
	if ((*tok_lst) && (*tok_lst)->cmd && (*tok_lst)->cmd->input)
		word->input = ft_strdup((*tok_lst)->cmd->input);
	else
		word->input = ft_strdup("");
	word->flag = (*tok_lst)->cmd->flag;
	if (*tok_lst && (*tok_lst)->next)
		*tok_lst = (*tok_lst)->next;
	return (word);
}

t_ast_node	*new_cmd_node(t_shell *shell, t_cmd *cmd, t_token **tok_lst)
{
	int			i;
	t_ast_node	*node;

	node = ft_calloc(sizeof(t_ast_node), 1);
	i = -1;
	while (++i < cmd->n - 1)
	{
		cmd->args[i] = ft_calloc(sizeof(t_input), 1);
		error_exit(!cmd->args, "malloc", 12);
		cmd->args[i]->flag = (*tok_lst)->cmd->flag;
		cmd->args[i]->input = ft_strdup((*tok_lst)->cmd->input);
		*tok_lst = (*tok_lst)->next;
	}
	if (cmd->n == 1)
		*tok_lst = (*tok_lst)->next;
	node->node = (void *)cmd;
	node->subshell_flag = 0;
	node->type = AST_COMMAND;
	node->next = parse_redir(shell, tok_lst);
	return (node);
}
