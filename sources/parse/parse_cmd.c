/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 03:31:24 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/28 10:07:37 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	word_count(t_token *tok_lst)
{
	int		n;

	n = 0;
	while (tok_lst && tok_lst->type == WORD)
	{
		n++;
		tok_lst = tok_lst->next;
	}
	return (n);
}

t_ast_node	*parse_simple_cmd(t_shell *shell, t_token **tok_lst)
{
	t_cmd		*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	error_exit(!cmd, "malloc", 12);
	cmd->n = word_count(*tok_lst);
	cmd->name = ft_calloc(sizeof(t_input), 1);
	error_exit(!cmd->name, "malloc", 12);
	cmd->name->flag = (*tok_lst)->cmd->flag;
	cmd->name->input = ft_strdup((*tok_lst)->cmd->input);
	if (cmd->n > 1)
	{
		*tok_lst = (*tok_lst)->next;
		cmd->args = ft_calloc(sizeof(t_input *), cmd->n - 1);
		error_exit(!cmd->args, "malloc", 12);
	}
	else
		cmd->args = NULL;
	return (new_cmd_node(shell, cmd, tok_lst));
}

t_ast_node	*parse_cmd_line(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*node;
	t_ast_node	*tmp;

	tmp = NULL;
	node = parse_redir(shell, tok_lst);
	if (node)
	{
		tmp = node;
		node = node->next;
	}
	if (*tok_lst && (*tok_lst)->type == BRACE_OPEN)
		node = parse_subshell(shell, tok_lst);
	else if (*tok_lst && (*tok_lst)->type != AND_OP \
	&& (*tok_lst)->type != OR_OP && (*tok_lst)->type != PIPE_OP \
	&& (*tok_lst)->type != BRACE_CLOSE)
		node = parse_simple_cmd(shell, tok_lst);
	if (tmp)
		node = tmp;
	return (node);
}

t_ast_node	*parse_subshell(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*node;

	node = NULL;
	*tok_lst = (*tok_lst)->next;
	node = line_parsing(shell, tok_lst);
	if ((*tok_lst)->type == BRACE_CLOSE)
		*tok_lst = (*tok_lst)->next;
	node->subshell_flag = 1;
	node->next = parse_redir(shell, tok_lst);
	return (node);
}
