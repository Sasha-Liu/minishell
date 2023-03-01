/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:56:06 by hsliu             #+#    #+#             */
/*   Updated: 2022/12/02 17:20:37 by hsliu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

//n number of member, each is size byte
//memory is initialize to 0
//should not test if n and size are zero
void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	ptr = malloc(n * size);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, n * size);
	return (ptr);
}
