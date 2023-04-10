/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:45:51 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/10 16:13:53 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

void	exec(t_shell *shell)
{
	int	i;

	i = 0;
	set_exec_signals();
	while (i < shell->cmd_size)
	{
		shell->cmd[i].child_pid = fork();
		if (shell->cmd[i].child_pid == -1)
		{
			perror("Fork");
			g_exit_status = 1;
			ft_exit_standart(shell);
		}
		if (shell->cmd[i].child_pid == 0)
		{
			if (launch(shell, i) == 1)
				g_exit_status = 1;
			ft_exit_standart(shell);
		}
		i ++;
	}
	if (close_all(shell) == 1)
		g_exit_status = 1;
	ft_wait(shell);
	ft_exit_standart(shell);
}
