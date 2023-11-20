/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:59:04 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/14 11:06:49 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define ERR_CD			"minishell: cd: HOME not set 🏠\n"
# define ERR_CD_2MUCH	"minishell: cd: too many arguments\n"
# define ERR_EXIT		"minishell: exit: too many arguments\n"
# define ERR_HIST		"minishell: history: too many arguments\n"
# define ERR_EXPORT		"minishell: export:"
# define ERR_UNSET		"minishell: unset:"
# define ERR_MSG		"minishell: syntax error near unexpected token `"
# define ERR_EOF		"minishell: unexpected EOF while looking for matching `"
# define ERR_SYN_ERR	"minishell: syntax error: unexpected end of file\n"
# define PERROR_MSG		"minishell"
# define HERE_MAX_ERR	"minishell: maximum here-document count exceeded\n"
# define SQUOTES_ERR	"minishell: unclosed \' quote 😇\n"
# define DQUOTES_ERR	"minishell: unclosed \" quote 😇\n"

# define EQUAL		'='
# define OR_IF		"||"
# define AND_IF		"&&"
# define LESS		'<'
# define GREAT		'>'
# define DLESS		"<<"
# define DGREAT		">>"
# define DOLLAR		'$'
# define PIPE		'|'
# define LBRACE		'('
# define RBRACE		')'
# define SQUOTES	'\''
# define DQUOTES	'\"'
# define EXIT_CODE	'?'
# define WILDCARD	'*'

# define PS			"minishell-4.2$ "

# define OPERATORS	"()<>|&"

typedef enum e_token_type
{
	HEREDOC,
	APPEND,
	FILE_IN,
	FILE_OUT,
	ENV_PARAM,
	PIPE_OP,
	AND_OP,
	OR_OP,
	BRACE_OPEN,
	BRACE_CLOSE,
	WORD,
	ERROR
}	t_token_type;

typedef enum e_flags
{
	F_DOLLAR			= 1 << 0,
	F_SQUOTES			= 1 << 1,
	F_DQUOTES			= 1 << 2,
	F_ASSIGNMENT		= 1 << 3,
	F_PARAM_SUBSHELL	= 1 << 4,
	F_PIPE_SUBSHELL		= 1 << 5,
	F_MUL_DOLLAR		= 1 << 6
}	t_flags;

typedef enum e_ast_node_type {
	AST_COMMAND,
	AST_WORD,
	AST_PIPE,
	AST_LOGICAL_OP,
	AST_REDIRECTION,
	AST_PARENTHESES,
	AST_ERROR
}	t_ast_node_type;

typedef struct s_stack
{
	char			c;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_input
{
	int		flag;
	char	*input;
}	t_input;

typedef struct s_token
{
	t_token_type	type;
	t_input			*cmd;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	int					subshell_flag;
	char				*err_mss;
	void				*node;
	struct s_ast_node	*next;
	struct s_ast_node	*prev;
}	t_ast_node;

typedef struct s_pipe
{
	int			in_fd;
	int			out_fd;
	t_ast_node	*left;
	t_ast_node	*right;
}	t_pipe;

typedef struct s_redir
{
	int				fd;
	t_token_type	type;
	t_ast_node		*filename;
}	t_redir;

typedef struct s_operator
{
	t_token_type	type;
	t_ast_node		*left;
	t_ast_node		*right;
}	t_operator;

typedef struct s_cmd
{
	char	*name;
	char	**args;
}	t_cmd;

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	int				hidden;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_shell
{
	char		**env;
	t_env		*env_lst;
	char		*line;
	t_token		*token_head;
	t_ast_node	*tree;
	int			ex_code;
	int			err;
	char		**path;
	int			history_fd;
	char		*hist_path;
	int			all_fds[FOPEN_MAX];
}	t_shell;
#endif
