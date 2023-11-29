/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:39:35 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/29 06:37:19 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_stat = 0;

static void	minishell_init(int argc, char **argv, char **envp, t_shell *shell)
{
	(void)argv;
	if (argc != 1)
		exit(0);
	shell->env = NULL;
	get_env(shell, envp);
	printf("\033[34m       _     _     _       _ _ \n\033[0m");
	printf("\033[34m _____|_|___|_|___| |_ ___| | |\n\033[0m");
	printf("\033[34m|     | |   | |_ -|   | -_| | |\n\033[0m");
	printf("\033[34m|_|_|_|_|_|_|_|___|_|_|___|_|_|\n\033[0m");
	printf("\033\n[34m Authors: mnazarya, ahovakim\n\n\033[0m");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_token	*tok_lst;

	minishell_init(argc, argv, envp, &shell);
	while (1)
	{
		g_stat = 0;
		shell.ex_code = 0;
		shell.err = 0;
		shell.err_msg = ft_strdup("");
		sig_init(&shell);
		shell.line = readline(PS);
		set_status(&shell);
		eof_handler(&shell);
		if (!shell.line)
			continue ;
		tok_lst = input_scanner(&shell, shell.line);
		check_open_close(&shell);
		shell.token_head = tok_lst;
		shell_history(&shell);
		token_free(&shell.token_head);
		free(shell.line);
		if (g_stat < 0)
		{
			ft_putendl_fd(shell.err_msg, 2);
			free(shell.err_msg);
			continue ;
		}
		free(shell.err_msg);
	}
	return (0);
}
