/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:49:22 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/11 17:30:10 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*initialize_name(char **envp, int i, int j)
{
	char	*res;
	int		k;

	k = 0;
	res = ft_calloc(sizeof(char), j + 1);
	error_exit(!res, "malloc", 12);
	while (k < j)
	{
		res[k] = envp[i][k];
		k++;
	}
	res[k] = '\0';
	return (res);
}

char	*initialize_value(char **envp, int i, int j)
{
	char	*res;
	int		k;

	k = 0;
	res = ft_calloc(sizeof(char), strlen(envp[i]) - j + 1);
	while (envp[i][++j])
	{
		res[k] = envp[i][j];
		k++;
	}
	res[k] = '\0';
	return (res);
}

static t_env	*get_env_list(t_env *cur)
{
	cur->hidden = 0;
	cur->next = ft_calloc(sizeof(t_env), 1);
	error_exit(!cur->next, "malloc", 12);
	cur->next->next = NULL;
	cur->next->prev = cur;
	return (cur->next);
}

t_env	*get_env(char **envp)
{
	t_env	*head;
	t_env	*cur;
	int		i;
	int		j;

	i = -1;
	head = ft_calloc(sizeof(t_env), 1);
	error_exit(!head, "malloc", 12);
	cur = head;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j])
		{
			if (envp[i][j] == '=')
			{
				cur->var_name = initialize_name(envp, i, j);
				cur->var_value = initialize_value(envp, i, j);
				break ;
			}
		}
		if (envp[i + 1])
			cur = get_env_list(cur);
	}
	return (add_hidden_values(head), head);
}
