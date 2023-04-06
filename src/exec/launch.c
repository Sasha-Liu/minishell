/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:19:57 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/06 15:13:34 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

int	get_path(t_shell *shell, int i)
{
	if (ft_strcmp(shell->cmd[i].args[0], "echo") == 0
		|| ft_strcmp(shell->cmd[i].args[0], "cd") == 0
		|| ft_strcmp(shell->cmd[i].args[0], "pwd") == 0
		|| ft_strcmp(shell->cmd[i].args[0], "export") == 0
		|| ft_strcmp(shell->cmd[i].args[0], "unset") == 0
		|| ft_strcmp(shell->cmd[i].args[0], "env") == 0
		|| ft_strcmp(shell->cmd[i].args[0], "exit") == 0)
	{
		return (0);
	}
	if (ft_strnstr(shell->cmd[i].args[0], "/",
			ft_strlen(shell->cmd[i].args[0])) != NULL)
	{
		if (direct_path(shell->cmd[i].args) == 1)
			return (1);
	}
	else
	{
		if (find_path(&shell->cmd[i].args[0], shell->env_tab) == 1)
			return (error_cmd(shell->cmd[i].args[0]), 1);
	}
	i ++;
	return (0);
}

int	ft_open(t_cmd *cmd)
{
	int	fd;

	if (cmd->read_file != NULL)
	{
		fd = open(cmd->read_file, O_RDONLY);
		if (fd == -1)
			return (perror(cmd->read_file), 1);
		cmd->read_fd = fd;
	}
	if (cmd->write_file != NULL)
	{
		fd = open(cmd->write_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(cmd->write_file), 1);
		cmd->write_fd = fd;
	}
	if (cmd->append_file != NULL)
	{
		fd = open(cmd->append_file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			return (perror(cmd->append_file), 1);
		cmd->write_fd = fd;
	}
	return (0);
}

int	ft_dup(t_shell *shell, int i)
{	
	if (ft_open(&shell->cmd[i]) == 1)
	{
		g_exit_status = 1;
		return (1);
	}
	close_pipe(shell, i);
	if (shell->cmd[i].read_fd != 0)
	{
		if (dup2(shell->cmd[i].read_fd, STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
		if (close(shell->cmd[i].read_fd) != 0)
			return (perror("Close"), 1);
	}
	if (shell->cmd[i].write_fd != 1)
	{
		if (dup2(shell->cmd[i].write_fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		if (close(shell->cmd[i].write_fd) != 0)
			return (perror("Close"), 1);
	}
	return (0);
}

int	launch(t_shell *shell, int i)
{
	if (shell->cmd[i].read_fd == -1)
		exit (130);
	if (get_path(shell, i) == 1)
	{
		g_exit_status = 127;
		exit (127);
	}
	if (ft_dup(shell, i) == 1)
		exit (1);
	if (ft_strnstr(shell->cmd[i].args[0], "/",
			ft_strlen(shell->cmd[i].args[0])) != NULL)
	{
		if (execve(shell->cmd[i].args[0], shell->cmd[i].args,
				shell->env_tab) == -1)
		return (perror("execve"), 1);
	}
	else
	{
		builtin(shell, i);
	}
	return (0);
//	exit (0);
}
