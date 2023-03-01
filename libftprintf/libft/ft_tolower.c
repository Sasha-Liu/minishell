/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:02:31 by hsliu             #+#    #+#             */
/*   Updated: 2022/11/14 22:32:15 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	char	x;

	x = (char)c;
	if (c >= 0 && c <= 127)
	{
		if (x >= 'A' && x <= 'Z')
			return (x + 'a' - 'A');
	}
	return (c);
}