/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:28:18 by mnazarya          #+#    #+#             */
/*   Updated: 2023/11/23 02:13:28 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_status(t_shell *shell)
{
	char	*status;

	status = ft_itoa(shell->ex_code);
	add_env_node(1, "?", status, shell->env_lst);
	free(status);
	return (shell->ex_code);
}
