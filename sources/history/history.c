/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:09:53 by mnazarya          #+#    #+#             */
/*   Updated: 2023/10/05 15:10:19 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_history(t_shell *shell)
{
	int		n;
	char	*str;

	n = 1;
	shell->history_fd = open(shell->hist_path, O_RDONLY);
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

static char	*find_home(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
			return (ft_strchr(envp[i], '/'));
		i++;
	}
	return (NULL);
}

void	shell_history(t_shell *shell, char **envp)
{	
	static int	i = -1;
	static char	*str;

	if (++i == 0)
	{
		str = ft_strdup("");
		shell->hist_path = ft_strjoin(find_home(envp), "/.minishell_history");
	}
	if (shell->line == NULL || ft_strcmp(shell->line, "") == 0)
		return ;
	shell->history_fd = open(shell->hist_path, O_CREAT \
	| O_WRONLY | O_APPEND, 0644);
	if (shell->history_fd == -1 && error(1, "history", 9, shell))
		return ;
	if (ft_strcmp(shell->line, str) && shell->line[0] != ' ')
	{
		ft_putendl_fd(shell->line, shell->history_fd);
		add_history(shell->line);
	}
	free(str);
	str = ft_strdup(shell->line);
	close(shell->history_fd);
}
