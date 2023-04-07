/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:06:57 by sasha             #+#    #+#             */
/*   Updated: 2023/04/07 16:02:24 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_write_protected(char *str, int size);

int	ft_echo(char **argv)
{
	int	i;

	i = 1;
	if (argv[1] == NULL)
		return (ft_write_protected("\n", 1));
	if (ft_strncmp(argv[1], "-n", 3) == 0)
		i = 2;
	while (argv[i])
	{
		if (ft_write_protected(argv[i], ft_strlen(argv[i])))
			return (1);
		if (argv[i + 1])
		{
			if (ft_write_protected(" ", 1))
				return (1);
		}
		i++;
	}
	if (ft_strncmp(argv[1], "-n", 3) == 0)
		return (0);
	if (ft_write_protected("\n", 1))
		return (1);
	return (0);
}

static int	ft_write_protected(char *str, int size)
{
	if (write(1, str, size) == -1)
	{
		return (1);
	}
	return (0);
}
