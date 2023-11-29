/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:17:48 by mnazarya          #+#    #+#             */
/*   Updated: 2023/08/04 15:17:48 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tok_lst(t_token *lst)
{
	while (lst)
	{
		printf ("token type: %d, token flag: %d, token input: %s\n", \
		lst->type, lst->cmd->flag, lst->cmd->input);
		lst = lst->next;
	}
}

t_token	*input_scanner(t_shell *shell, char *str)
{
	t_token	*tok_lst;
	t_token	*token;

	tok_lst = NULL;
	token = NULL;
	while (*str)
	{
		token = get_token(&str);
		token_add(&tok_lst, token);
	}
	shell->ex_code = token_analyser(shell, tok_lst);
	print_tok_lst(tok_lst);
	return (tok_lst);
}

void	token_free(t_token **tok_lst)
{
	t_token	*tmp;

	while (*tok_lst)
	{
		tmp = (*tok_lst)->next;
		free((*tok_lst)->cmd->input);
		free((*tok_lst)->cmd);
		free(*tok_lst);
		*tok_lst = tmp;
	}
}

int	token_analyser(t_shell *shell, t_token *tok_lst)
{
	t_token	*tmp;

	tmp = tok_lst;
	while (tmp && !shell->ex_code)
	{
		if (tmp->type == PIPE_OP || tmp->type == OR_OP || tmp->type == AND_OP)
			shell->ex_code = operator_analyser(shell, &tmp);
		else if (tmp->type == WORD)
			tmp = tmp->next;
		else if (tmp->type == BRACE_OPEN)
			shell->ex_code = brace_analyser(shell, &tmp);
		else if (tmp->type == HEREDOC || tmp->type == APPEND \
		|| tmp->type == FILE_IN || tmp->type == FILE_OUT)
			shell->ex_code = redirections_analyser(shell, &tmp);
		else if (tmp->type == BRACE_CLOSE)
			tmp = tmp->next;
		else if (tmp->type == ENV_PARAM)
			env_param_analizer(&tmp);
		else
			tmp = tmp->next;
	}
	tmp = tok_lst;
	if (g_stat == -2)
		search_heredoc(shell, tmp);
	return (set_status(shell));
}
