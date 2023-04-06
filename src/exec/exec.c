/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:45:51 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/06 15:19:08 by pchapuis         ###   ########.fr       */
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

int	exec(t_shell *shell)
{
	int	i;
	
	i = 0;
//	set_exec_signals();
	unplug_signals();
//	if (shell->cmd_size == 1)
//	{
//		launch(shell, i);
//		return (0);
//	}
	while (i < shell->cmd_size)
	{
		shell->cmd[i].child_pid = fork();
		if (shell->cmd[i].child_pid == -1)
			return (perror("Fork"), 1);
		if (shell->cmd[i].child_pid == 0)
		{
			set_exec_signals();
			if (launch(shell, i) == 1)
				return (1);
		}
		i ++;
	}
	if (close_all(shell) == 1)
		return (1);
	ft_wait(shell);
	return (0);
}
