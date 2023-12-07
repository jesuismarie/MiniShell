/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:10:54 by mnazarya          #+#    #+#             */
/*   Updated: 2023/12/04 15:01:09 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error(int cond, char *str, int ecode, t_shell *shell)
{
	if (cond)
	{
		perror(str);
		shell->ex_code = ecode;
		set_status(shell);
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

void	set_error_stat(int stat, t_token **lst)
{
	g_stat = stat;
	(*lst)->type = ERROR;
}
