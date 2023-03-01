/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:00:31 by hsliu             #+#    #+#             */
/*   Updated: 2023/01/02 10:40:56 by hsliu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_digit_10(unsigned int n);
static int	ft_count_digit_16(unsigned int n);

//print u x X depending on c
int	ft_print_unsigned(unsigned int n, char c, int *err)
{
	char	*hex_low;
	char	*hex_upp;
	int		res;

	hex_low = "0123456789abcdef";
	hex_upp = "0123456789ABCDEF";
	if (c == 'u')
	{
		res = ft_putnbr_unsigned(n);
		if (res != ft_count_digit_10(n))
			*err = -1;
		return (res);
	}	
	if (c == 'x')
		res = ft_putnbr_x(n, hex_low);
	else
		res = ft_putnbr_x(n, hex_upp);
	if (res != ft_count_digit_16(n))
		*err = -1;
	return (res);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n <= 9)
		count = count + ft_putchar('0' + n);
	else
	{
		count = count + ft_putnbr_unsigned(n / 10);
		count = count + ft_putchar('0' + n % 10);
	}
	return (count);
}

static int	ft_count_digit_10(unsigned int m)
{
	int	count;

	count = 1;
	while (m >= 10)
	{
		count++;
		m = m / 10;
	}
	return (count);
}

int	ft_putnbr_x(unsigned int n, char *hex)
{
	int		count;

	count = 0;
	if (n <= 15)
		count = count + ft_putchar(hex[n]);
	else
	{
		count = count + ft_putnbr_x(n / 16, hex);
		count = count + ft_putchar(hex[n % 16]);
	}
	return (count);
}

static int	ft_count_digit_16(unsigned int m)
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
