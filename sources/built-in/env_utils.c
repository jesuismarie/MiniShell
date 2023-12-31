/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:49:10 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/25 09:22:00 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_pid(void)
{
	char	*name;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exit(0);
	else
	{
		wait(&status);
		name = ft_itoa((int)pid - 1);
	}
	return (name);
}

int	env_lenght(t_shell *shell)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = shell->env_lst;
	while (tmp)
	{
		if (tmp->hidden == 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	add_hidden_values(t_shell *shell)
{
	char	*tmp;

	tmp = get_pid();
	add_env_node(1, "$", tmp, shell);
	add_env_node(1, "?", "0", shell);
	add_env_node(1, "PS1", PS, shell);
	add_env_node(1, "0", "minishell", shell);
	free(tmp);
	return (0);
}

void	init_env(t_shell *shell)
{
	int	i;

	i = -1;
	if (!shell->env)
	{
		shell->env = env_vars(shell);
		return ;
	}
	while (shell->env[++i])
		free(shell->env[i]);
	free(shell->env);
	shell->env = env_vars(shell);
}
