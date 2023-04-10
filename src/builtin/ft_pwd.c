/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:53:54 by sasha             #+#    #+#             */
/*   Updated: 2023/04/10 16:03:30 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*ft_malloc_getcwd(void);

int	ft_pwd(char **argv)
{
	char	*pwd;

	if (argv[1] && ft_strncmp(argv[1], "-", 1) == 0)
	{
		write(2, "pwd: invalid option\n", 21);
		return (2);
	}
	pwd = ft_malloc_getcwd();
	if (pwd == NULL)
	{
		return (1);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (0);
}

static char	*ft_malloc_getcwd(void)
{
	int		size;
	char	*buf;

	size = 100;
	while (size < 1000)
	{
		buf = malloc(sizeof(char) * size);
		if (buf == NULL)
		{
			write(2, "malloc fails\n", 14);
			return (NULL);
		}
		if (getcwd(buf, size) == NULL)
		{
			free(buf);
		}
		else
		{
			return (buf);
		}
		size += 100;
	}
	write(2, "pwd name exceeds 1000 characters\n", 34);
	return (NULL);
}
