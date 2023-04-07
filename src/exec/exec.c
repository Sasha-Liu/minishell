/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:45:51 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/07 14:45:30 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

int	exec(t_shell *shell)
{
	int	i;
	
	i = 0;
	set_exec_signals();
	while (i < shell->cmd_size)
	{
		shell->cmd[i].child_pid = fork();
		if (shell->cmd[i].child_pid == -1)
			return (perror("Fork"), 1);
		if (shell->cmd[i].child_pid == 0)
		{
			if (launch(shell, i) == 1)
				return (1);
		}
		i ++;
	}
	if (close_all(shell) == 1)
		return (1);
	ft_wait(shell);
	ft_exit_standart(shell);
	return (0);
}
