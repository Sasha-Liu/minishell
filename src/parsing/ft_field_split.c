/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_field_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:43:12 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/07 10:46:23 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_set_pointer(t_token *n1, t_token *n2, t_token *pre, t_token *nex)
{
	n1->prev = pre;
	n1->next = n2;
	n2->prev = n1;
	n2->next = nex;
	if (pre != NULL)
		pre->next = n1;
	if (nex != NULL)
		nex->prev = n2;
}

/*
    return 0
    return 1 when err
    if there are unquoted space in the word,
    the word must be splitted
*/
int	ft_split_lst(t_token **lst)
{
	int	err;

	err = 0;
	while (1)
	{
		err = ft_split_word(lst);
		if ((*lst)->next == NULL)
			break ;
		*lst = (*lst)->next;
	}
	while ((*lst)->prev != NULL)
	{
		*lst = (*lst)->prev;
	}
	if (err == 1)
	{
		write(2, "split fails\n", 12);
	}
	return (err);
}

/*
    return 0
	return 1 when err
	
	if node->word contain unquoted space,
    node is splitted into node1 and node2
    ft_split_lst with continue work on the next node
    (which is node2 in this case)
*/
int	ft_split_word(t_token **node)
{
	int		i;
	t_token	*node1;
	t_token	*node2;
	t_token	*prev;
	t_token	*next;

	prev = (*node)->prev;
	next = (*node)->next;
	i = ft_exist_unquoted_space((*node)->word);
	if (i == 0)
		return (0);
	node1 = ft_new_token((*node)->word, i);
	while ((*node)->word[i] == ' ')
		i++;
	node2 = ft_new_token((*node)->word + i, ft_strlen((*node)->word + i));
	if (!node1 || !node2)
	{
		free(node1);
		free(node2);
		return (1);
	}
	ft_set_pointer(node1, node2, prev, next);
	ft_delete_token(node);
	*node = node1;
	return (0);
}
