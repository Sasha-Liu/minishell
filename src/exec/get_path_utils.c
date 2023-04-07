/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:39:18 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/07 16:44:18 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

void	free_path(char **all_paths, char **cmd, int status)
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

char	*create_path(char *cmd, char *path_test)
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
