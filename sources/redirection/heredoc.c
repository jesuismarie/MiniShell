/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:53:59 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/28 13:23:08 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	here_sig_handler(int signal)
{
	(void)signal;
}

static void	here_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &here_sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}

void	fake_heredoc(t_shell *shell, t_token *lim)
{
	char	*line;
	t_input	*word;
	int		pid;

	pid = fork();
	if (error(pid < 0, PERROR_MSG, 1, shell))
		return ;
	if (pid == 0)
	{
		here_signal();
		word = lim->cmd;
		while (1)
		{
			line = readline("heredoc> ");
			if (!line || (word && word->input && !ft_strcmp(line, word->input)))
				break ;
			free(line);
		}
		exit(0);
	}
	waitpid(pid, &(shell->ex_code), 0);
}

void	heredoc(t_shell *shell, t_ast_node *lim, t_pipe	here)
{
	char	*line;
	char	*s;
	t_input	*word;

	here_signal();
	word = lim->node;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || (word && word->input && !ft_strcmp(line, word->input)))
			break ;
		s = line;
		if (!(word->flag & (SQUOTES | DQUOTES)))
			line = expand_param(shell, s);
		ft_putstr_fd(line, here.out_fd);
		if (s)
			free(s);
	}
	close(here.in_fd);
	close(here.out_fd);
	exit(0);
}

// static char	**find_path(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (!ft_strncmp(envp[i], "PATH=", 5))
// 			return (ft_split(ft_strchr(envp[i], '/'), ':'));
// 		i++;
// 	}
// 	return (NULL);
// }

// void	shell_heredoc(t_shell *shell)
// {
// 	if (pipe(fd) == -1)
// 		error_exit(1, "pipe", 1);
// }
