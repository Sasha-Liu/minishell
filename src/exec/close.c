/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:15:25 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/10 14:37:52 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

void	close_pipe(t_shell *shell, int nb)
{
	int	i;

	i = 0;
	while (i < shell->cmd_size)
	{
		if (i != nb)
		{
			close(shell->cmd[i].write_fd);
			close(shell->cmd[i].read_fd);
		}
		i ++;
	}
}

int	close_all(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_size)
	{
		if (shell->cmd[i].read_fd != 0 && shell->cmd[i].read_fd != -1)
		{
			if (close(shell->cmd[i].read_fd) != 0)
				return (perror("Close"), 1);
		}
		if (shell->cmd[i].write_fd != 1)
		{
			if (close(shell->cmd[i].write_fd) != 0)
				return (perror("Close"), 1);
		}
		i ++;
	}
	return (0);
}
