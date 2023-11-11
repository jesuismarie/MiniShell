/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:39:35 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/11 16:53:39 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_stat = 0;

static void	minishell_init(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		exit(0);
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

	minishell_init(argc, argv);
	shell.env_lst = get_env(envp);
	while (1)
	{
		g_stat = 0;
		sig_init(&shell);
		shell.line = readline(PS);
		eof_handler(&shell);
		check_open_close(shell.line);
		if (g_stat < 0 || !(shell.line))
			continue ;
		tok_lst = input_scanner(shell.line);
		shell.token_head = tok_lst;
		if (g_stat < 0 || !(shell.line))
			continue ;
		shell_history(&shell, envp);
		free(shell.line);
		token_free(&shell.token_head);
	}
	return (0);
}
