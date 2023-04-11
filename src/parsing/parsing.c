/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:41:29 by sasha             #+#    #+#             */
/*   Updated: 2023/04/11 15:58:52 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
    return 0
    return 1 when err
*/
int	ft_parsing(char *buffer, t_shell *shell)
{
	shell->lst = ft_line_to_token(buffer);
	if (!shell->lst || ft_syntax_err(shell->lst))
	{
		return (ft_delete_lst(&(shell->lst)), 1);
	}
	if (ft_exps_and_split(&(shell->lst), shell->env_lst))
	{
		return (ft_delete_lst(&(shell->lst)), 1);
	}
	shell->cmd = ft_get_cmd(shell->lst, &(shell->cmd_size));
	if (shell->cmd == NULL)
	{
		return (ft_delete_lst(&(shell->lst)), 1);
	}
	ft_redirect(&(shell->lst), shell->cmd, shell->cmd_size, shell);
	if (ft_init_command(shell->lst, shell->cmd, shell->cmd_size))
	{
		ft_free_cmd(shell->cmd, shell->cmd_size);
		return (ft_delete_lst(&(shell->lst)), 1);
	}
	return (ft_delete_lst(&(shell->lst)), 0);
}
