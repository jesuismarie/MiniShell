/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:17:48 by mnazarya          #+#    #+#             */
/*   Updated: 2023/08/04 15:17:48 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tok_lst(t_token *lst)
{
	while (lst)
	{
		printf ("token type: %d, token flag: %d, token input: %s\n", \
		lst->type, lst->cmd->flag, lst->cmd->input);
		lst = lst->next;
	}
}

t_token	*input_scanner(char *str)
{
	t_token	*tok_lst;
	t_token	*token;

	tok_lst = NULL;
	token = NULL;
	while (*str)
	{
		token = get_token(&str);
		token_add(&tok_lst, token);
	}
	print_tok_lst(tok_lst);
	return (tok_lst);
}

void	token_free(t_token **tok_lst)
{
	t_token	*tmp;

	while (*tok_lst)
	{
		tmp = (*tok_lst)->next;
		free((*tok_lst)->cmd->input);
		free((*tok_lst)->cmd);
		free(*tok_lst);
		*tok_lst = tmp;
	}
}
