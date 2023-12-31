/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:09:53 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/07 21:19:35 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_history(t_shell *shell)
{
	int		n;
	char	*str;

	n = 1;
	shell->history_fd = open(shell->hist, O_RDONLY);
	while (1)
	{
		str = get_next_line(shell->history_fd);
		if (!str)
			break ;
		printf("   %d %s", n++, str);
		free(str);
		str = NULL;
	}
	close(shell->history_fd);
}

static char	*find_home(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, "HOME"))
			return (tmp->var_value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	shell_history(t_shell *shell)
{
	static int		i = -1;
	static char		*str;

	if (++i == 0)
	{
		str = ft_strdup("");
		shell->hist = ft_strjoin(find_home(shell->env_lst), \
		"/.minishell_history");
	}
	if (shell->line == NULL || ft_strcmp(shell->line, "") == 0)
		return ;
	shell->history_fd = open(shell->hist, O_CREAT \
	| O_WRONLY | O_APPEND, 0644);
	if (shell->history_fd == -1 && error(1, "history", 9, shell))
		return ;
	if (ft_strcmp(shell->line, str) && shell->line[0] != ' ')
	{
		add_history(shell->line);
		if (g_stat != -3)
			ft_putendl_fd(shell->line, shell->history_fd);
	}
	free(str);
	str = ft_strdup(shell->line);
	close(shell->history_fd);
}
