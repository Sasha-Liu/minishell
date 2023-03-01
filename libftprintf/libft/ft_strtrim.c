/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 00:18:06 by hsliu             #+#    #+#             */
/*   Updated: 2022/12/27 10:31:09 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

//static int		ft_isset(char const *set, char c);
static size_t	ft_trimlen(char const *s1, char const *set);

//set is a string of char to be trimmed
//trim char from head and tail of s1
//return the trimmed string
//return  null on fail
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	trimlen;
	size_t	start;
	size_t	i;
	char	*ptr;

	trimlen = ft_trimlen(s1, set);
	start = 0;
	i = 0;
	ptr = (char *)malloc((trimlen + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (i < trimlen)
	{
		ptr[i] = s1[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
static int	ft_isset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
*/

static size_t	ft_trimlen(char const *s1, char const *set)
{
	size_t	len;
	size_t	head;
	size_t	tail;
	size_t	trim;

	len = ft_strlen(s1);
	head = 0;
	tail = len - 1;
	trim = 0;
	if (len == 0)
		return (0);
	while (s1[head] && ft_strchr(set, s1[head]))
	{
		head++;
		trim++;
	}
	while (tail >= head && ft_strchr(set, s1[tail]))
	{
		tail--;
		trim++;
	}
	if (len < trim)
		return (0);
	return (len - trim);
}
