/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:00:28 by sasha             #+#    #+#             */
/*   Updated: 2023/04/07 11:32:25 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

void	ft_print_lst(t_token *lst)
{
	if (!lst)
	{
		printf("lst empty\n");
	}
	while (lst)
	{
		printf("%s -> ", lst->word);
		lst = lst->next;
	}
}

void	ft_print_cmd(t_cmd *cmd, int size)
{
	int	i;
	int	j;

	i = 0;
	printf("size: %d\n", size);
	while (i < size)
	{
		printf("\n");
		printf("cmd %d: ", i);
		j = 0;
		if (*(cmd[i].args[0]) == '\0')
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

int main()
{
	t_shell shell;
	char    *buffer;
	int		pid;

	if (ft_init_shell(&shell))
	{
		return (1);
	}
	g_exit_status = 0;
	while (1)
	{
		set_interactive_signals();
		rl_on_new_line();
		buffer = readline("minishell-> ");
		if (buffer == NULL)
			break ;
		if (ft_parsing(buffer, &shell))
			write(2, "parsing fails\n", 14);
		else
		{
			//ft_print_cmd(shell.cmd, shell.cmd_size);
			add_history(buffer);
			unplug_signals();
			pid = fork();
			if (pid == 0)
			{
				if (exec(&shell) == 1)
					return (ft_exit_standart(&shell), 1);
				exit (g_exit_status);
			}
			int wstatus;
			waitpid(pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				g_exit_status = WEXITSTATUS(wstatus);
			if (WIFSIGNALED(wstatus))
			{
				g_exit_status = WTERMSIG(wstatus);
				if (g_exit_status != 131)
					g_exit_status += 128;
			}
			if (ft_strnstr(shell.cmd[0].args[0], "/",
					ft_strlen(shell.cmd[0].args[0])) == NULL && shell.cmd_size == 1)
			{
				builtin(&shell, 0, 0);
			}
			//ft_print_cmd(shell.cmd, shell.cmd_size);
		}
		ft_free_cmd(shell.cmd, shell.cmd_size);
		shell.cmd = NULL;
		*buffer = '\0';
		free(buffer);
	}
	ft_exit_without_free(&shell);
	return (1);
}
