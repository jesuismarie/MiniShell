/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analyser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:06:04 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/18 20:46:03 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	operator_analyser(t_token **tok_lst)
{
	if ((*tok_lst)->type == PIPE_OP || (*tok_lst)->type == OR_OP \
	|| (*tok_lst)->type == AND_OP)
	{
		if (!(*tok_lst)->next || !(*tok_lst)->prev || ((*tok_lst)->next \
		&& ((*tok_lst)->next->type == PIPE_OP \
		|| (*tok_lst)->next->type == OR_OP \
		|| (*tok_lst)->next->type == AND_OP)))
		{
			ft_putstr_fd(ERR_MSG, 1);
			ft_putstr_fd((*tok_lst)->next->cmd->input, 1);
			ft_putstr_fd("'");
			g_stat = -1;
			return (2);
		}
		else
			*tok_lst = (*tok_lst)->next;
	}
	return (0);
}

int	brace_analyser(t_token **tok_lst)
{
	if ((*tok_lst)->type == BRACE_OPEN)
	{
		if ((*tok_lst)->next && (*tok_lst)->next->type != WORD)
		{
			ft_putstr_fd(ERR_MSG, 1);
			ft_putendl_fd("(\'", 1);
			g_stat = -1;
			return (2);
		}
		else
			*tok_lst = (*tok_lst)->next;
	}
	return (0);
}

int	redirections_analyser(t_token **tok_lst)
{
	if ((*tok_lst)->type == HEREDOC || (*tok_lst)->type == APPEND \
	|| (*tok_lst)->type == FILE_IN || (*tok_lst)->type == FILE_OUT)
	{
		if (!(*tok_lst)->next)
		{
			ft_putstr_fd(ERR_MSG, 1);
			ft_putendl_fd("newline'", 1);
			g_stat = -1;
			return (2);
		}
		else if ((*tok_lst)->next && ((*tok_lst)->next->type != WORD \
		|| (*tok_lst)->next->type != ENV_PARAM))
		{
			ft_putstr_fd(ERR_MSG, 1);
			ft_putstr_fd((*tok_lst)->next->cmd->input, 1);
			ft_putstr_fd("'");
			g_stat = -1;
			return (2);
		}
		else
			tmp = tmp->next;
	}
}

int	token_analyser(t_shell *shell, t_token *tok_lst)
{
	t_token	*tmp;

	tmp = tok_lst;
	while (tmp)
	{
		shell->ex_code = operator_analyser(&tok_lst);
		if (tmp->type == WORD && !shell->ex_code)
			tmp = tmp->next;
		shell->ex_code = brace_analyser(&tok_lst);
		else if (tmp->type == BRACE_CLOSE && !shell->ex_code)
			tmp = tmp->next;
		else if (tmp->type == ENV_PARAM && !shell->ex_code)
		{
			if (!tmp->next)
				tmp->type = WORD;
			else if (tmp->next->type != WORD || tmp->next->type != ENV_PARAM)
				return(printf("need2change\n")); //"inch vor syntax error gci, to eta. es xosqi sra depqn a $<< $| $> i tak dalee"
			else
				tmp = tmp->next;
		}
		else if (!shell->ex_code)
			tmp = tmp->next;
		
	}
	return (set_status(shell));
}