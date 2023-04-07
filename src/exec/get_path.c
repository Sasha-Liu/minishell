/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:10:26 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/07 16:27:08 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

static void	free_path(char **all_paths, char **cmd, int status)
{
	int	i;

	if (status == 0)
		free(*cmd);
	i = 0;
	while (all_paths[i] != NULL)
	{
		free(all_paths[i]);
		i ++;
	}
	free(all_paths);
}

static char	*create_path(char *cmd, char *path_test)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(path_test, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, cmd);
	free(temp);
	if (!path)
		return (NULL);
	return (path);
}

char	**find_all_paths(char **envp, char **cmd)
{
	char	**all_paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i ++;
	if (envp[i] == NULL)
	{
		write(2, "bash: ", 7);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": No such file or directory\n", 29);
		exit(127);
	}
	all_paths = ft_split(ft_strnstr(envp[i], "PATH", 4), ':');
	if (!all_paths)
		return (NULL);
	return (all_paths);
}

int	find_path(char **cmd, char **envp)
{
	char	**all_paths;
	char	*path;
	int		i;

	all_paths = find_all_paths(envp, cmd);
	if (!all_paths)
		return (1);
	i = 0;
	while (all_paths[i])
	{
		path = create_path(*cmd, all_paths[i]);
		if (!path)
			return (1);
		if (access(path, X_OK) == 0)
		{
			free_path(all_paths, cmd, 0);
			*cmd = ft_strdup(path);
			free(path);
			if (!cmd)
				return (1);
			return (0);
		}
		free(path);
		i ++;
	}
	return (free_path(all_paths, cmd, 1), 1);
}

int	direct_path(char **cmd)
{
	int	i;
	int	fd;

	i = 0;
	while (!cmd[0][i] || cmd[0][i] != '/')
		i ++;
	if (!cmd[0][i + 1] || (cmd[0][i + 1] == '.' && !cmd[0][i + 2]))
		return (write(2, cmd[0], ft_strlen(cmd[0])),
			write(2, ": is a directory\n", 17), 1);
	fd = open(cmd[0], O_RDONLY);
	if (fd != -1 || access(cmd[0], X_OK) == 0)
		return (0);
	else
	{
		if (fd != -1)
			close(fd);
		return (perror(cmd[0]), 1);
	}
}
