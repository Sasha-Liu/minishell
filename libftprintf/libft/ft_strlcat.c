/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:25:32 by hsliu             #+#    #+#             */
/*   Updated: 2022/12/02 16:34:13 by hsliu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
//append src to dest, it appends at most n - strlen(dest) - 1 byte 
//and null terminate the result
//return value is strlen(src) + strlen(dest)
size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	if (n < dest_len)
		return (ft_strlen(src) + n);
	while (src[i] && (i + 1) < (n - dest_len))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (ft_strlen(src) + dest_len);
}
