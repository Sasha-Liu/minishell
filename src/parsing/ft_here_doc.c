/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:43:28 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/11 16:36:47 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parsing.h"

static void	ft_free_shell(t_shell *shell);

int	ft_here_doc(char *limiter, t_shell *shell)
{
	int		fd[2];
	int		pid;
	int		wstatus;

	unplug_signals();
	if (pipe(fd) == -1)
	{
		write(2, "heredoc: pipe fails\n", 20);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		write(2, "heredoc: fork fails\n", 20);
		return (-1);
	}
	if (pid == 0)
		ft_child_here_doc(limiter, fd, shell);
	close(fd[1]);
	wait(&wstatus);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (-1);
	g_exit_status = 0;
	return (fd[0]);
}

void	ft_child_here_doc(char *limiter, int *fd, t_shell *shell)
{
	char	*input;

	close(fd[0]);
	while (1)
	{
		set_heredoc_signals();
		input = readline("heredoc> ");
		if (input == NULL)
		{
			write(2, "warning: heredoc delimited by eof\n", 34);
			close(fd[1]);
			ft_free_shell(shell);
			exit(0);
		}
		if (ft_strncmp(input, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(input);
			close(fd[1]);
			ft_free_shell(shell);
			exit(0);
		}
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
}

static void	ft_free_shell(t_shell *shell)
{
	if (shell->env_lst)
		ft_delete_lst(&(shell->env_lst));
	if (shell->lst)
		ft_delete_lst(&(shell->lst));
	ft_free_cmd(shell->cmd, shell->cmd_size);
	if (shell->env_tab)
		ft_free_env_array(&(shell->env_tab));
}
