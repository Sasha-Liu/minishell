/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:40:27 by hsliu             #+#    #+#             */
/*   Updated: 2022/12/06 14:15:11 by hsliu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_digit_16(unsigned long m);

//print a string or a pointer depends on c
int	ft_print_ptr(void *p, char c, int *err)
{
	unsigned long	m;
	int				res;

	if (c == 's' && p == NULL)
	{
		res = ft_putstr("(null)");
		if (res != 6)
			*err = -1;
		return (res);
	}	
	if (c == 's')
	{
		res = ft_putstr((char *)p);
		if (res != (int)ft_strlen((char *)p))
			*err = -1;
		return (res);
	}
	m = (unsigned long)p;
	ft_putstr("0x");
	res = ft_puthex(m);
	if (res != ft_count_digit_16(m))
		*err = -1;
	return (res + 2);
}

//print pointer in hexdecimal
int	ft_puthex(unsigned long m)
{
	char	*hex;
	int		count;

	hex = "0123456789abcdef";
	count = 0;
	if (m < 16)
		count = count + ft_putchar(hex[m]);
	else
	{
		count = count + ft_puthex(m / 16);
		count = count + ft_putchar(hex[m % 16]);
	}
	return (count);
}

static int	ft_count_digit_16(unsigned long m)
{
	int	count;

	count = 1;
	while (m >= 16)
	{
		count++;
		m = m / 16;
	}
	return (count);
}
