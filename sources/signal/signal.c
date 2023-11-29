/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:57:01 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/26 07:06:09 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	quit_handler(void)
{
	return (0);
}

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_stat = SIGINT;
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	eof_handler(t_shell *shell)
{
	if (!shell->line)
	{
		write(1, "\033[Aminishell-4.2$ exit\n", 23);
		exit(shell->ex_code);
	}
}

void	sig_init(t_shell *shell)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (g_stat == SIGINT)
		shell->ex_code = 128 + g_stat;
	if (error(sigaction(SIGINT, &sa, NULL) == -1, \
	"Sigaction error ❌", 128 + SIGINT, shell))
		return ;
	// if (error(sigaction(SIGQUIT, &sa, NULL) == -1,
	// "Sigaction error ❌", 128 + SIGQUIT))
	// 	return ;
	rl_catch_signals = 0;
	rl_event_hook = &quit_handler;
}
