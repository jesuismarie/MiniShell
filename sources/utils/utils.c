/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:28:18 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/29 21:29:17 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*join_with_symbol(char *s1, char *s2, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	str[j++] = c;
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

void	set_err(t_shell *shell, char *str)
{
	if (shell->err_msg && ft_strcmp(shell->err_msg, ""))
		return ;
	free(shell->err_msg);
	shell->err_msg = ft_strdup(str);
}

void	search_heredoc(t_shell *shell, t_token *tok_lst)
{
	t_token	*tmp;

	tmp = tok_lst;
	shell->ex_code = 0;
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
		if (tmp->prev->type == HEREDOC && shell->ex_code == 0)
			fake_heredoc(shell, tmp);
	}
}

int	set_status(t_shell *shell)
{
	char	*status;

	status = ft_itoa(shell->ex_code);
	add_env_node(1, "?", status, shell);
	free(status);
	return (shell->ex_code);
}
