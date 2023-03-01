/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:31:06 by hsliu             #+#    #+#             */
/*   Updated: 2022/12/05 10:44:08 by hsliu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

//no more than n char are compared
//written : while (i < n - needle_len + 1)
char	*ft_strnstr(const char *hay, const char *needle, size_t n)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	i = 0;
	if (needle_len == 0)
		return ((char *)hay);
	if (*hay == '\0')
		return (NULL);
	while (hay[i] && i < n)
	{
		if (ft_strncmp(needle, hay + i, needle_len))
			i++;
		else
		{
			if (n >= i + needle_len)
				return ((char *)(hay + i));
			return (NULL);
		}
	}
	return (NULL);
}
