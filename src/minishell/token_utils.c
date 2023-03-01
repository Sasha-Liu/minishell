/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:46:19 by sasha             #+#    #+#             */
/*   Updated: 2023/03/01 16:26:12 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
	malloc a token with argument
*/
t_token	*ft_new_token(char *str, int size)
{
	char	*word;
	t_token	*token;

	word = ft_strndup(str, size);
	token = malloc(sizeof(t_token));
	if (word == NULL || token == NULL)
	{
		free(word);
		free(token);
		write(2, "malloc fails\n", 13);
		return (NULL);
	}
	token->word = word;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

/*
	add token from the end of list
*/
void	ft_add_token(t_token **lst, t_token *token)
{
	t_token	*node;

	node = *lst;
	if (*lst == NULL)
	{
		*lst = token;
		return ;
	}
	while (node->next)
	{
		node = node->next;
	}
	node->next = token;
	token->prev = node;
}

/*
	token should be extracted first 
*/
void	ft_delete_token(t_token **token)
{
	free((*token)->word);
	free(*token);
	*token = NULL;
}

/*
	delete and free the list
*/
void	ft_delete_lst(t_token **lst)
{
	t_token	*node;
	t_token	*next;

	node = *lst;
	while (node)
	{
		next = node->next;
		free(node->word);
		free(node);
		node = next;
	}
	*lst = NULL;
}

int	ft_lstlen(t_token *lst)
{
	t_token	*node;
	int		i;

	node = lst;
	i = 0;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}
