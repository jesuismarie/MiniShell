/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analyser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:06:04 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/23 07:16:44 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	operator_analyser(t_token **lst)
{
	if (!(*lst)->prev)
	{
		ft_putstr_fd(ERR_MSG, 1);
		ft_putstr_fd((*lst)->cmd->input, 1);
		ft_putendl_fd("'", 1);
		g_stat = -1;
		return (2);
	}
	else if (!(*lst)->next || ((*lst)->next && ((*lst)->next->type == PIPE_OP \
	|| (*lst)->next->type == OR_OP || (*lst)->next->type == AND_OP)))
	{
		ft_putstr_fd(ERR_MSG, 1);
		if ((*lst)->next)
			ft_putstr_fd((*lst)->next->cmd->input, 1);
		else
			ft_putstr_fd((*lst)->cmd->input, 1);
		ft_putendl_fd("'", 1);
		g_stat = -1;
		return (2);
	}
	else
		*lst = (*lst)->next;
	return (0);
}

int	brace_analyser(t_token **lst)
{
	if ((*lst)->next && ((*lst)->next->type == HEREDOC \
	|| (*lst)->next->type == APPEND \
	|| (*lst)->next->type == FILE_IN || (*lst)->next->type == FILE_OUT))
	{
		if ((*lst)->next->next->type != WORD \
		&& (*lst)->next->next->type != ENV_PARAM)
		{
			ft_putstr_fd(ERR_MSG, 1);
			g_stat = -1;
			return (ft_putendl_fd(")\'", 1), 2);
		}
		else
			*lst = (*lst)->next;
	}
	if ((*lst)->next && ((*lst)->next->type == PIPE_OP \
	|| (*lst)->next->type == OR_OP || (*lst)->next->type == AND_OP))
	{
		ft_putstr_fd(ERR_MSG, 1);
		g_stat = -1;
		return (ft_putendl_fd("(\'", 1), 2);
	}
	else
		*lst = (*lst)->next;
	return (0);
}

int	redirections_analyser(t_token **lst)
{
	if (!(*lst)->next)
	{
		ft_putstr_fd(ERR_MSG, 1);
		ft_putendl_fd("newline'", 1);
		g_stat = -1;
		return (2);
	}
	else if ((*lst)->next && ((*lst)->next->type != ENV_PARAM \
	&& (*lst)->next->type != WORD))
	{
		ft_putstr_fd(ERR_MSG, 1);
		ft_putstr_fd((*lst)->next->cmd->input, 1);
		ft_putendl_fd("'", 1);
		g_stat = -1;
		return (2);
	}
	else
		*lst = (*lst)->next;
	return (0);
}

void	env_param_analizer(t_token **lst)
{
	if (!ft_strcmp((*lst)->cmd->input, "$"))
	{
		(*lst)->type = WORD;
		(*lst)->cmd->flag ^= F_DOLLAR;
	}
	*lst = (*lst)->next;
}

int	token_analyser(t_shell *shell, t_token *tok_lst)
{
	t_token	*tmp;

	tmp = tok_lst;
	while (tmp && !shell->ex_code)
	{
		if (tmp->type == PIPE_OP || tmp->type == OR_OP || tmp->type == AND_OP)
			shell->ex_code = operator_analyser(&tmp);
		else if (tmp->type == WORD)
			tmp = tmp->next;
		else if (tmp->type == BRACE_OPEN)
			shell->ex_code = brace_analyser(&tmp);
		else if (tmp->type == HEREDOC || tmp->type == APPEND \
		|| tmp->type == FILE_IN || tmp->type == FILE_OUT)
			shell->ex_code = redirections_analyser(&tmp);
		else if (tmp->type == BRACE_CLOSE)
			tmp = tmp->next;
		else if (tmp->type == ENV_PARAM)
			env_param_analizer(&tmp);
		else
			tmp = tmp->next;
	}
	return (set_status(shell));
}
