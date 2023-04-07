/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_homedir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:58:26 by sasha             #+#    #+#             */
/*   Updated: 2023/04/07 10:33:20 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
	login is delimit by back slash zero or slash
	~login/ return 6
*/
int	ft_delimit_login(char *login)
{
	int	i;

	i = 0;
	while (login[i] && login[i] != '/')
	{
		i++;
	}
	return (i);
}

/*
	login start with ~ and end with back slash zero or slash
	ex: ~LOGIN or ~LOGIN/
	cannot call this function when login is empty string
	return Null when fails or login does not exist
*/
char	*ft_get_homedir(char *login)
{
	char	*line;
	char	*homedir;
	char	**split_line;
	int		i;

	line = ft_find_line(login);
	if (!line)
		return (NULL);
	split_line = ft_split(line, ':');
	if (!split_line)
	{
		write(2, "malloc fails\n", 13);
		return (free(line), NULL);
	}
	homedir = ft_strdup(split_line[5]);
	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	if (!homedir)
		write(2, "malloc fails\n", 13);
	return (free(line), free(split_line), homedir);
}

/*
    search in /etc/passwd to find the line start with login
    and return the line
*/
char	*ft_find_line(char *login)
{
	int		fd;
	char	*line;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd < 0)
	{
		write(2, "open fails\n", 11);
		return (NULL);
	}
	login++;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || ft_strncmp(line, login, ft_delimit_login(login)) == 0)
		{
			break ;
		}
		free(line);
	}
	close(fd);
	return (line);
}
