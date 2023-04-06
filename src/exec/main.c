/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:00:28 by sasha             #+#    #+#             */
/*   Updated: 2023/04/06 15:19:23 by pchapuis         ###   ########.fr       */
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

	if (ft_get_env(&shell))
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
			add_history(buffer);
			//le nouveau fork permet de conserver les actions des signaux apres execve
		//	unplug_signals();
		//	int	pid;
		//	pid = fork();
		//	if (pid == 0)
		//	{
				if (exec(&shell) == 1)
					return (ft_exit_standart(&shell), 1);
		//		exit (0);
		//	}
		//	waitpid(pid, NULL, 0);
			
		//	ft_print_cmd(shell.cmd, shell.cmd_size);
			if (ft_strcmp(shell.cmd->args[0], "exit") == 0 && test_exit(shell.cmd->args) == 1)
				ft_exit_standart(&shell);
		}
		ft_free_cmd(shell.cmd, shell.cmd_size);
		shell.cmd = NULL;
		*buffer = '\0';
		free(buffer);
	}
	ft_exit_without_free(&shell);
	return (1);
}
