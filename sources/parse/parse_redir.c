/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:19:52 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/24 07:24:59 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast_node	*parse_redir(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*node;
	t_redir		*redir_node;

	node = ft_calloc(sizeof(t_ast_node), 1);
	redir_node = ft_calloc(sizeof(t_redir), 1);
	error_exit(!redir_node, "malloc", 12);
	redir_node->type = (*tok_lst)->type;
	*tok_lst = (*tok_lst)->next;
	node->type = AST_REDIRECTION;
	redir_node->filename = parse_filename(tok_lst);
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

t_ast_node	*parse_filename(t_token **tok_lst)
{
	t_ast_node	*node;

	node = NULL;
	node = new_word_node(tok_lst);
	if (*tok_lst && (*tok_lst)->next)
		*tok_lst = (*tok_lst)->next;
	return (node);
}
