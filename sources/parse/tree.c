/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:25:46 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/02 18:26:01 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast_node	*tree_builder(t_shell *shell, t_token *tok_lst);

t_token	*find_head(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->prev)
	{
		if ((int)tmp->type == 5 || (int)tmp->type == 6 \
			|| (int)tmp->type == 7)
			return (printf("Head is: %s\n", tmp->cmd->input), tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}
