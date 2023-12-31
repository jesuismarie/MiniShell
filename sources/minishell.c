/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:39:35 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/28 10:18:37 by mnazarya         ###   ########.fr       */
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
	printf("\033[1;34m       _     _     _       _ _ \n\033[0m");
	printf("\033[1;34m _____|_|___|_|___| |_ ___| | |\n\033[0m");
	printf("\033[1;34m|     | |   | |_ -|   | -_| | |\n\033[0m");
	printf("\033[1;34m|_|_|_|_|_|_|_|___|_|_|___|_|_|\n\033[0m");
	printf("\n\033[1;34m Authors: mnazarya, ahovakim\n\n\033[0m");
}

static	void	prompt_init(t_shell *shell)
{
	g_stat = 0;
	shell->ex_code = 0;
	shell->err = 0;
	shell->err_msg = ft_strdup("");
	sig_init(shell);
	shell->line = readline(PS);
	set_status(shell);
	eof_handler(shell);
}

void	prompt_validation(t_shell *shell)
{
	shell->token_head = input_scanner(shell->line);
	check_brace(shell, &(shell->token_head));
	shell->ex_code = token_analyser(shell, shell->token_head);
	check_open_close(shell);
	if (g_stat < 0)
		search_heredoc(shell, shell->token_head);
	check_here_count(shell);
	shell_history(shell);
	free(shell->line);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_token	*tok;

	minishell_init(argc, argv, envp, &shell);
	while (1)
	{
		prompt_init(&shell);
		if (!shell.line)
			continue ;
		prompt_validation(&shell);
		if (g_stat < 0)
		{
			ft_putendl_fd(shell.err_msg, 2);
			free(shell.err_msg);
			token_free(&(shell.token_head));
			continue ;
		}
		tok = shell.token_head;
		shell.tree = line_parsing(&shell, &tok);
		print_ast(shell.tree, 1);
		token_free(&(shell.token_head));
		free_ast(&(shell.tree));
		free(shell.err_msg);
	}
	return (0);
}

void	print_tok_lst(t_token *lst)
{
	printf("\n----TOKEN LIST----\n");
	while (lst)
	{
		printf ("token type: %d, token flag: %d, token input: %s\n", \
		lst->type, lst->cmd->flag, lst->cmd->input);
		lst = lst->next;
	}
}

void	print_ast(t_ast_node *node, int n)
{
	static int	c = 1;
	int			i;
	int			j;
	t_operator	*op;
	t_pipe		*pipe;
	t_redir		*red;
	t_cmd		*cmd;

	if (!node)
		return ;
	if (++c < 1)
		printf("\n----AST----\n");
	i = -1;
	while (++i < n - 1)
		printf("	");
	if (node->type == AST_LOGICAL_OP)
	{
		op = (t_operator *)node->node;
		if (op->type == 6)
			printf("&&(%d)\n", node->subshell_flag);
		else
			printf("||(%d)\n", node->subshell_flag);
		print_ast(op->left, n + 1);
		print_ast(op->right, n + 1);
	}
	else if (node->type == AST_REDIRECTION)
	{
		red = (t_redir *)node->node;
		printf("(---%d---) ", node->subshell_flag);
		while (red)
		{
			if (red->type == 0)
				printf("<< ");
			else if (red->type == 1)
				printf(">> ");
			else if (red->type == 2)
				printf("< ");
			else
				printf("> ");
			printf("%s(%d), ", red->filename->input, red->filename->flag);
			red = red->next;
		}
		printf("\n");
	}
	else if (node->type == AST_PIPE)
	{
		pipe = (t_pipe *)node->node;
		printf("|(%d)\n", node->subshell_flag);
		print_ast(pipe->left, n + 1);
		print_ast(pipe->right, n + 1);
	}
	else if (node->type == AST_COMMAND)
	{
		cmd = (t_cmd *)node->node;
		printf("(---%d---)", node->subshell_flag);
		printf("%s(%d), ", cmd->name->input, cmd->name->flag);
		j = -1;
		while (++j < cmd->n - 1)
			printf("%s(%d), ", cmd->args[j]->input, cmd->args[j]->flag);
		if (!node->next)
			printf("\n");
	}
	print_ast(node->next, n);
}
