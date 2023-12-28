/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:28:18 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/23 18:12:55 by mnazarya         ###   ########.fr       */
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
	str = ft_calloc(sizeof(*s1), (ft_strlen(s1) + ft_strlen(s2) + 2));
	error_exit(!str, "malloc", 12);
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
	while (tmp && tmp->type != ERROR)
	{
		if (tmp->type == HEREDOC)
			fake_heredoc(shell, tmp->next);
		tmp = tmp->next;
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
