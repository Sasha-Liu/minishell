/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:09:31 by hsliu             #+#    #+#             */
/*   Updated: 2023/03/02 16:15:35 by hsliu            ###   ########.fr       */
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
		close(fd[0]);
		ft_child_here_doc(limiter, fd);
		exit(0);
	}
	close(fd[1]);
	wait(&wstatus);
	return (fd[0]);
}

void	ft_child_here_doc(char *limiter, int *fd)
{
	char	*input;

	close(fd[0]);
	while (1)
	{
		write(1, "heredoc> ", 9);
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
		{
			write(2, "warning: heredoc delimited by eof\n", 34);
			close(fd[1]);
			return ;
		}
		if (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(input) == (ft_strlen(limiter) + 1))
		{
			free(input);
			close(fd[1]);
			return ;
		}
		write(fd[1], input, ft_strlen(input));
		free(input);
	}
}
