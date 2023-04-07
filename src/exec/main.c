/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:00:28 by sasha             #+#    #+#             */
/*   Updated: 2023/04/07 16:52:28 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

void	ft_print_cmd(t_cmd *cmd, int size)
{
	int	i;
	int	j;

	i = 0;
	printf("size: %d\n", size);
	while (i < size)
	{
		printf("\n");
		printf("cmd %d: \n", i);
		j = 0;
		if (cmd[i].args == NULL)
		{
			printf("(empty)\n");
		}
		while (cmd[i].args && cmd[i].args[j])
		{
			printf("_%s_", cmd[i].args[j]);
			j++;
		}
		printf("\n");
		printf("read_file %s \n", cmd[i].read_file);
		printf("read_fd %d \n", cmd[i].read_fd);
		printf("write_file %s \n", cmd[i].write_file);
		printf("write_fd %d \n", cmd[i].write_fd);
		printf("append_file %s \n", cmd[i].append_file);
		i++;
	}
	printf("\n");
}

void	reset(t_shell *shell, char *buffer)
{
	ft_free_cmd(shell->cmd, shell->cmd_size);
	shell->cmd = NULL;
	*buffer = '\0';
	free(buffer);
}

int	launch_execution(t_shell *shell, char *buffer)
{
	int	pid;

	add_history(buffer);
	unplug_signals();
	pid = fork();
	if (pid == -1)
		return (perror("Fork"), 1);
	if (pid == 0)
	{
		if (exec(shell) == 1)
			g_exit_status = 1;
		ft_exit_standart(shell);
	}
	if (close_all(shell) == 1)
		return (1);
	wait_solo_process(pid);
	if (check_builtin(shell, 0) == 1 && shell->cmd_size == 1)
	{
		if (ft_dup(shell, 0) == 1)
			return (1);
		builtin(shell, 0, 0);
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
		if (!ft_parsing(buffer, &shell))
		{
			if (launch_execution(&shell, buffer) == 1)
			{
				g_exit_status = 1;
				ft_exit_standart(&shell);
			}
		//	ft_print_cmd(shell.cmd, shell.cmd_size);
		}
		reset(&shell, buffer);
	}
	ft_exit_without_free(&shell);
	return (1);
}
