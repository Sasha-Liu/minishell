/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:01:03 by hsliu             #+#    #+#             */
/*   Updated: 2022/12/05 10:18:04 by hsliu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_strrev(char *s);
static size_t	ft_count(long long m);
static char		*ft_math(long long m, int sign);

//convert integer to string, negative must be handled
char	*ft_itoa(int n)
{
	char		*ptr;
	int			sign;
	long long	m;

	sign = 0;
	m = (long long)n;
	if (m < 0)
	{
		sign = -1;
		m = -m;
	}
	ptr = ft_math(m, sign);
	return (ptr);
}

static char	*ft_math(long long num, int sign)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (sign == -1)
		ptr = (char *)malloc(sizeof(char) * (ft_count(num) + 2));
	else
		ptr = (char *)malloc(sizeof(char) * (ft_count(num) + 1));
	if (ptr == 0)
		return (ptr);
	if (num == 0)
		ptr[i++] = '0';
	while (num > 0)
	{
		ptr[i] = (num % 10) + '0';
		num = num / 10;
		i++;
	}
	if (sign == -1)
		ptr[i++] = '-';
	ptr[i] = '\0';
	ft_strrev(ptr);
	return (ptr);
}

//count how many digit there will be in the number
//this function does not count the terminating NULL
//n is positive, this function doesn't deal with negativity 
static size_t	ft_count(long long num)
{
	size_t	count;

	count = 1;
	while (num >= 10)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

//reverse a string
static void	ft_strrev(char *s)
{
	char	temp;
	int		head;
	int		tail;

	head = 0;
	tail = ft_strlen(s) - 1;
	while (head < tail)
	{
		temp = s[head];
		s[head] = s[tail];
		s[tail] = temp;
		head++;
		tail--;
	}
}
