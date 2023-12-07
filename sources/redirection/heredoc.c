/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:53:59 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/07 20:50:04 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	here_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_stat = 10;
		rl_done = 1;
	}
}

static void	here_signal(t_shell *shell)
{
	struct sigaction	sa;

	sa.sa_handler = &here_sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (error(sigaction(SIGINT, &sa, NULL) == -1, \
	"Sigaction error ❌", 128 + SIGINT, shell))
		return ;
	rl_catch_signals = 0;
}

static void	fake_here_child(t_shell *shell, t_input *word)
{
	char	*line;

	while (1)
	{
		here_signal(shell);
		line = readline("heredoc> ");
		if (!line || (word && word->input && !ft_strcmp(line, word->input)))
		{
			if (line)
				free (line);
			break ;
		}
		if (g_stat == 10)
		{
			shell->ex_code = 1;
			set_status(shell);
			return ;
		}
		free(line);
	}
}

void	fake_heredoc(t_shell *shell, t_token *lim)
{
	t_input	*word;
	int		pid;

	pid = fork();
	if (error(pid < 0, PERROR_MSG, 1, shell))
		return ;
	if (pid == 0)
	{
		word = lim->cmd;
		fake_here_child(shell, word);
		exit(0);
	}
	waitpid(pid, &(shell->ex_code), 0);
}

void	heredoc(t_shell *shell, t_ast_node *lim, t_pipe	here)
{
	char	*line;
	char	*s;
	t_input	*word;

	here_signal(shell);
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
