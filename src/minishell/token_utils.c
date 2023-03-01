/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:46:19 by sasha             #+#    #+#             */
/*   Updated: 2023/02/17 17:12:18 by vburton          ###   ########.fr       */
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
	extract the token from list
*/
t_token	*ft_extract_token(t_token **lst, t_token *token)
{
	t_token	*prev;
	t_token	*next;

	if (*lst == token)
	{
		*lst = token->next;
	}
	prev = token->prev;
	next = token->next;
	if (prev)
	{
		prev->next = next;
	}
	if (next)
	{
		next->prev = prev;
	}
	token->prev = NULL;
	token->next = NULL;
	return (token);
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
