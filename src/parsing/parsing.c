/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:41:29 by sasha             #+#    #+#             */
/*   Updated: 2023/03/01 12:41:18 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
    return 0
    return 1 when err
*/
int	ft_parsing(char *buffer, t_shell *shell)
{
	t_token	*lst;
	t_cmd	*cmd;

	lst = ft_line_to_token(buffer);
	if (!lst || ft_syntax_err(lst))
	{
		return (ft_delete_lst(&lst), 1);
	}
	if (ft_exps_and_split(&lst, shell->env_lst))
	{
		return (ft_delete_lst(&lst), 1);
	}
	cmd = ft_get_cmd(lst, &(shell->cmd_size));
	if (cmd == NULL)
	{
		return (ft_delete_lst(&lst), 1);
	}
	ft_redirect(&lst, cmd, shell->cmd_size);
	if (ft_init_command(lst, cmd, shell->cmd_size))
	{
		ft_free_cmd(cmd, shell->cmd_size);
		return (ft_delete_lst(&lst), 1);
	}
	shell->cmd = cmd;
	return (ft_delete_lst(&lst), 0);
}
