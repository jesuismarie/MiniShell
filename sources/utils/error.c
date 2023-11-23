/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:10:54 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/11 17:32:23 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error(int cond, char *str, int ecode, t_shell *shell)
{
	if (cond)
	{
		perror(str);
		shell->ex_code = ecode;
		g_stat = -1;
		return (1);
	}
	return (0);
}

void	error_exit(int cond, char *str, int ecode)
{
	if (cond)
	{
		perror(str);
		exit(ecode);
	}
}

// t_ast_node	*parsing_error(t_token **tok_lst)
// {
// 	t_ast_node	*node;
// 	char		*str;

// 	node = ft_calloc(sizeof(t_ast_node), 1);
// 	error_exit(!node, "malloc", 12);
// 	if (!(*tok_lst))
// 		node->err_mss = ft_strdup(ERR_SYN_ERR);
// 	else
// 	{
// 		str = ft_strjoin(ERR_MSG, (*tok_lst)->cmd->input);
// 		node->err_mss = str;
// 	}
// 	node->type = AST_ERROR;
// 	return (node);
// }
