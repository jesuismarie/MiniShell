/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:19:52 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/26 14:38:55 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_redir	*parse_helper(t_shell *shell, t_token **tok_lst)
{
	t_redir	*redir_lst;
	t_redir	*tmp;

	redir_lst = NULL;
	while ((*tok_lst) && ((*tok_lst)->type == HEREDOC \
	|| (*tok_lst)->type == APPEND || (*tok_lst)->type == FILE_IN \
	|| (*tok_lst)->type == FILE_OUT))
	{
		if (redir_lst)
		{
			redir_lst->next = new_redir_node(shell, tok_lst);
			redir_lst->next->next = NULL;
			redir_lst = redir_lst->next;
		}
		else
		{
			redir_lst = new_redir_node(shell, tok_lst);
			redir_lst->next = NULL;
			tmp = redir_lst;
		}
	}
	return (tmp);
}

t_ast_node	*parse_redir(t_shell *shell, t_token **tok_lst)
{
	t_ast_node	*redir;

	redir = NULL;
	if ((*tok_lst) && ((*tok_lst)->type == HEREDOC \
	|| (*tok_lst)->type == APPEND || (*tok_lst)->type == FILE_IN \
	|| (*tok_lst)->type == FILE_OUT))
	{
		redir = ft_calloc(sizeof(t_ast_node), 1);
		error_exit(!redir, "malloc", 12);
		redir->type = AST_REDIRECTION;
		redir->node = (void *)parse_helper(shell, tok_lst);
		redir->subshell_flag = 0;
	}
	return (redir);
}

int	parse_heredoc(t_shell *shell, t_input *lim)
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
