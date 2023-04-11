/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:00:28 by sasha             #+#    #+#             */
/*   Updated: 2023/04/11 14:27:18 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

void	reset(t_shell *shell, char *buffer)
{
	ft_free_cmd(shell->cmd, shell->cmd_size);
	shell->cmd = NULL;
	*buffer = '\0';
	free(buffer);
}

int	launch_execution(t_shell *shell)
{
	int	pid;

	unplug_signals();
	pid = fork();
	if (pid == -1)
		return (perror("Fork"), 1);
	if (pid == 0)
	{
		exec(shell);
		ft_exit_standart(shell);
	}
	if (close_all(shell) == 1)
		return (1);
	wait_solo_process(pid);
	if (check_builtin(shell, 0) == 1 && shell->cmd_size == 1)
	{
		if (ft_dup(shell, 0) == 1)
			return (1);
		g_exit_status = builtin(shell, 0, 0);
	}
	return (0);
}

int	main(void)
{
	t_shell	shell;
	char	*buffer;

	if (ft_init_shell(&shell))
		return (1);
	while (1)
	{
		set_interactive_signals();
		rl_on_new_line();
		buffer = readline("minishell-> ");
		if (buffer == NULL)
			break ;
		add_history(buffer);
		if (!ft_parsing(buffer, &shell))
		{
			if (launch_execution(&shell) == 1)
			{
				g_exit_status = 1;
				ft_exit_standart(&shell);
			}
		}
		reset(&shell, buffer);
	}
	ft_exit_without_free(&shell);
	return (1);
}
