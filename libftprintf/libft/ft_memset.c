/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:15:00 by hsliu             #+#    #+#             */
/*   Updated: 2022/11/12 21:44:55 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	c_byte;

	c_byte = (char)c;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c_byte;
		i++;
	}
	return (s);
}
