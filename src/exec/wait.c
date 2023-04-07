/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:45:18 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/07 15:50:37 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

void	ft_wait(t_shell *shell)
{
	int	i;
	int	waitstatus;
	int	status;

	i = 0;
	while (i < shell->cmd_size)
	{
		waitpid(shell->cmd[i].child_pid, &waitstatus, 0);
		if (WIFEXITED(waitstatus))
			status = WEXITSTATUS(waitstatus);
		if (WIFSIGNALED(waitstatus))
		{
			status = WTERMSIG(waitstatus);
			if (status != 131)
				status += 128;
		}
		g_exit_status = status;
		i ++;
	}
}

void	wait_solo_process(int pid)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_exit_status = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
	{
		g_exit_status = WTERMSIG(wstatus);
		if (g_exit_status != 131)
			g_exit_status += 128;
	}
}
