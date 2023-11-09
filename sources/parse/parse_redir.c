/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:59:30 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/09 14:59:31 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redir_filename(t_token *tok_lst)
{
	if (!tok_lst && tok_lst->type != WORD && \
		tok_lst->type != BRACE_OPEN && tok_lst->type != ENV_PARAM)
		return (1);
	return (0);
}

t_ast_node	*parse_redir(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*node;
	t_redir		*redir_node;

	node = ft_calloc(sizeof(t_ast_node), 1);
	if (shell->err != 0)
		return (node);
	redir_node = malloc(sizeof(t_redir));
	error_exit(!redir_node, "malloc", 12);
	redir_node->type = (*tok_lst)->type;
	*tok_lst = (*tok_lst)->next;
	if (redir_filename(*tok_lst))
		return (parsing_error(tok_lst));
	node->type = AST_REDIRECTION;
	redir_node->filename = parse_word(shell, tok_lst);
	if (redir_node->type == HEREDOC)
		redir_node->fd = parse_heredoc(shell, redir_node->filename);
	return (node);
}

int	parse_heredoc(t_shell *shell, t_ast_node *lim)
{
	t_pipe	here;
	int		fds[2];
	int		pid;

	if (error(pipe(fds) == -1, PERROR_MSG, 1, shell))
		return (-1);
	here.in_fd = fds[0];
	here.out_fd = fds[1];
	pid = fork();
	if (error(pid < 0, PERROR_MSG, 1, shell))
		return (-1);
	if (pid == 0)
		heredoc(shell, lim, here);
	waitpid(pid, &(shell->ex_code), 0);
	if (WIFSIGNALED(shell->ex_code))
	{
		if (WTERMSIG(shell->ex_code) == SIGINT)
			write(1, "\n", 1);
		here.in_fd = -1;
	}
	return (here.in_fd);
}

t_ast_node	*parse_word(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*node;

	node = NULL;
	if (shell->err != 0)
		return (node);
	if (redir_filename(*tok_lst))
		return (parsing_error(tok_lst));
	node = new_word_node(tok_lst);
	if (*tok_lst && (*tok_lst)->next)
		*tok_lst = (*tok_lst)->next;
	return (node);
}
