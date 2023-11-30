/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:46:27 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/30 17:26:56 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <define.h>
# include <sys/wait.h>
# include <get_next_line.h>
# include <readline/history.h>
# include <readline/readline.h>

extern int	g_stat;

/*----------------------------------------------------------------------------*/
/*----------------------------- LEXICAL ANALIZER -----------------------------*/
/*----------------------------------------------------------------------------*/
void		quote_check(char *line, int *i);
void		check_open_close(t_shell *shell);
void		check_brace(t_shell *shell, t_token **tok_lst);
void		clear_stack(t_stack **brace);
void		operator_input(t_token *node);
int			get_op_type(char **s);
t_token		*get_operator_token(char **s);
t_input		*get_word(char **s);
t_token		*get_word_token(char **s);
t_token		*input_scanner(char *str);
t_token		*get_token(char **s);
void		token_add(t_token **tok_lst, t_token *token);
void		token_free(t_token **tok_lst);
int			operator_analyser(t_shell *shell, t_token **lst);
int			brace_analyser(t_shell *shell, t_token **lst);
int			redirections_analyser(t_shell *shell, t_token **lst);
void		env_param_analizer(t_token **lst);
int			token_analyser(t_shell *shell, t_token *tok_lst);

/*----------------------------------------------------------------------------*/
/*---------------------------------- PARSER ----------------------------------*/
/*----------------------------------------------------------------------------*/
t_ast_node	*new_word_node(t_token **tok_lst);
void		token_consume(t_token **scanner);
t_ast_node	*line_parsing(t_shell *shell, t_token **tok_lst);
t_ast_node	*parse_pipeline(t_shell *shell, t_token **tok_lst);
void		node_push(t_ast_node **node_list, t_ast_node *to_push);
t_ast_node	*parse_filename(t_token **tok_lst);
t_ast_node	*parse_redir(t_shell *shell, t_token **tok_lst);
int			parse_heredoc(t_shell *shell, t_ast_node *lim);

/*----------------------------------------------------------------------------*/
/*------------------------------------ CD ------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*----------------------------------- ECHO -----------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*----------------------------------- ENV ------------------------------------*/
/*----------------------------------------------------------------------------*/
char		*get_pid(void);
char		*initialize_name(char **envp, int i, int j);
char		*initialize_value(char **envp, int i, int j);
int			add_hidden_values(t_shell *shell);
void		get_env(t_shell *shell, char **envp);
char		*search_var(t_env *env, char *var_name);
void		add_env_node(int hidden, char *name, char *value, t_shell *shell);
void		del_env_node(char *var_name, t_shell *shell);
int			env_lenght(t_shell *shell);
char		**env_vars(t_shell *shell);
void		init_env(t_shell *shell);

/*----------------------------------------------------------------------------*/
/*----------------------------------- EXIT -----------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*---------------------------------- EXPORT ----------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*----------------------------------- PWD ------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*---------------------------------- UNSET -----------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*--------------------------------- HISTORY ----------------------------------*/
/*----------------------------------------------------------------------------*/
void		shell_history(t_shell *shell);
void		print_history(t_shell *shell);

/*----------------------------------------------------------------------------*/
/*----------------------------------- PIPE -----------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*------------------------------- REDIRECTION --------------------------------*/
/*----------------------------------------------------------------------------*/
void		fake_heredoc(t_shell *shell, t_token *lim);
void		heredoc(t_shell *shell, t_ast_node *lim, t_pipe	here);

/*----------------------------------------------------------------------------*/
/*---------------------------------- SIGNAL ----------------------------------*/
/*----------------------------------------------------------------------------*/
void		sig_init(t_shell *shell);
void		eof_handler(t_shell *shell);

/*----------------------------------------------------------------------------*/
/*---------------------------------- UTILS -----------------------------------*/
/*----------------------------------------------------------------------------*/
char		*expand_param(t_shell *shell, char *str);
int			error(int cond, char *str, int ecode, t_shell *shell);
void		error_exit(int cond, char *str, int ecode);
void		set_err(t_shell *shell, char *str);
void		set_error_stat(int stat, t_token **lst);
char		*join_with_symbol(char *s1, char *s2, char c);
void		search_heredoc(t_shell *shell, t_token *lst);
int			set_status(t_shell *shell);

#endif
