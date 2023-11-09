#include <minishell.h>

char	*initialize_name(char **envp, int i, int j)
{
	char	*res;
	int		k;

	k = 0;
	res = malloc(j + 1);
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
	res = malloc(strlen(envp[i]) - j + 1);
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
	cur->next = malloc(sizeof(t_env));
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
	head = malloc(sizeof(t_env));
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
		cur = get_env_list(cur);
	}
	return (head);
}
