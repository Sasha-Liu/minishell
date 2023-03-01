/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:14:22 by hsliu             #+#    #+#             */
/*   Updated: 2023/01/02 10:43:22 by hsliu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static int	ft_putchar_err(char c, int *err);

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		count;
	int		err;
	int		res;

	if (write(1, 0, 0) != 0)
		return (-1);
	count = 0;
	err = 0;
	va_start(ap, fmt);
	res = ft_print(ap, fmt, &count, &err);
	va_end(ap);
	if (err == -1)
		return (-1);
	return (res);
}

int	ft_print(va_list ap, const char *fmt, int *cnt, int *err)
{
	while (*fmt)
	{
		if (*fmt != '%')
			*cnt += ft_putchar_err(*fmt, err);
		else
		{
			fmt++;
			if (*fmt == 'c' || *fmt == 'd' || *fmt == 'i')
				*cnt += ft_print_int(va_arg(ap, int), *fmt, err);
			else if (*fmt == 's' || *fmt == 'p')
				*cnt += ft_print_ptr(va_arg(ap, void *), *fmt, err);
			else if (*fmt == 'u' || *fmt == 'x' || *fmt == 'X')
				*cnt += ft_print_unsigned(va_arg(ap, unsigned int), *fmt, err);
			else if (*fmt == '%')
				*cnt += ft_putchar_err(*fmt, err);
			else
				*err = -1;
		}
		if (*err == -1)
			return (-1);
		fmt++;
	}
	return (*cnt);
}

static int	ft_putchar_err(char c, int *err)
{
	int	res;

	res = write(1, &c, 1);
	if (res == -1)
		*err = -1;
	return (res);
}
