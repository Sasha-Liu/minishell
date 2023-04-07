/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:14:43 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/07 10:37:20 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
    iterate through the list,
    remove quote from every word
*/
void	ft_rm_quote_lst(t_token *lst)
{
	while (lst != NULL)
	{
		ft_rm_quote_word(lst->word);
		lst = lst->next;
	}
}

/*
    remove quote from a word
    ex:
    "Hello 'world' ~" become Hello 'world' ~
*/
void	ft_rm_quote_word(char *word)
{
	int	quote_st;
	int	write_pos;
	int	read_pos;

	quote_st = 0;
	write_pos = 0;
	read_pos = 0;
	while (word[read_pos])
	{
		if (quote_st == 0 && (word[read_pos] == '\'' || word[read_pos] == '"'))
			quote_st = ft_set_quote_state(word[read_pos], quote_st);
		else if (quote_st == 1 && word[read_pos] == '\'')
			quote_st = ft_set_quote_state(word[read_pos], quote_st);
		else if (quote_st == 2 && word[read_pos] == '"')
			quote_st = ft_set_quote_state(word[read_pos], quote_st);
		else
		{
			word[write_pos] = word[read_pos];
			write_pos++;
		}
		read_pos++;
	}
	word[write_pos] = word[read_pos];
}
