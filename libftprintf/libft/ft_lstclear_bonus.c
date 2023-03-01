/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:23:53 by hsliu             #+#    #+#             */
/*   Updated: 2022/11/18 13:11:44 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *lst;
	if (*lst == NULL)
		return ;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		del(prev->content);
		free(prev);
		prev = NULL;
	}
	*lst = NULL;
}
