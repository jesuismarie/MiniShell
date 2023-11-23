/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:49:10 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/23 02:12:33 by mnazarya         ###   ########.fr       */
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

void	add_env_node(int hidden, char *var_name, char *var_val, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp && !ft_strcmp(var_name, tmp->var_name))
		{
			free(tmp->var_value);
			tmp->var_value = ft_strdup(var_val);
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = ft_calloc(sizeof(t_env), 1);
	error_exit(!tmp->next, "malloc", 12);
	tmp->next->var_name = ft_strdup(var_name);
	tmp->next->var_value = ft_strdup(var_val);
	tmp->hidden = hidden;
	tmp->next->prev = tmp;
}

void	del_env_node(char *var_name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(var_name, tmp->var_name))
		{
			free(tmp->var_name);
			free(tmp->var_value);
			if (tmp->next)
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			else
				tmp->prev->next = NULL;
			free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

int	add_hidden_values(t_env *head)
{
	char	*tmp;

	tmp = get_pid();
	add_env_node(1, "$", tmp, head);
	add_env_node(1, "?", "0", head);
	add_env_node(1, "PS1", PS, head);
	add_env_node(1, "0", "minishell", head);
	free(tmp);
	return (0);
}

char	*search_var(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp && !ft_strcmp(var_name, tmp->var_name))
			return (tmp->var_value);
		tmp = tmp->next;
	}
	return (NULL);
}
