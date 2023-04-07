/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:43:28 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/07 12:12:34 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parsing.h"

int	ft_here_doc(char *limiter)
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
	{
		ft_child_here_doc(limiter, fd);
	}
	close(fd[1]);
	wait(&wstatus);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (-1);
	return (fd[0]);
}

void	ft_child_here_doc(char *limiter, int *fd)
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
			exit(0);
		}
		if (ft_strcmp(input, limiter) == 0)
		{
			free(input);
			close(fd[1]);
			exit(0);
		}
		write(fd[1], input, ft_strlen(input));
		free(input);
	}
}
