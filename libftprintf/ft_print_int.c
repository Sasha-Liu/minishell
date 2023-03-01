/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:15:38 by hsliu             #+#    #+#             */
/*   Updated: 2022/12/06 14:16:43 by hsliu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_digit(int n);

//print char or integer, depending on the char c
//return -1 on error
int	ft_print_int(int n, char c, int *err)
{
	int	res;

	if (c == 'c')
	{
		res = ft_putchar((char)n);
		if (res == -1)
			*err = -1;
		return (res);
	}			
	res = ft_putnbr(n);
	if (res != ft_count_digit(n))
		*err = -1;
	return (res);
}

static int	ft_count_digit(int n)
{
	int	count;

	if (n == -2147483648)
		return (11);
	count = 1;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
