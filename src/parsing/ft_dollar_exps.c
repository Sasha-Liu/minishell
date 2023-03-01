/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_exps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 22:29:44 by sasha             #+#    #+#             */
/*   Updated: 2023/02/10 16:25:06 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_init_local_var(char *word, int *quote_st, int *i, char **new_w)
{
	*i = 0;
	*quote_st = ft_set_quote_state(word[0], 0);
	*new_w = malloc(sizeof(char));
	if (*new_w == NULL)
	{
		write(2, "malloc fails\n", 13);
		return ;
	}
	**new_w = '\0';
}

/*
    content of envp has the form:
    key=value
    if *word has part that's quoted by single quote, no change
    otherwise, every "$key" will be replaced with "value"
    $key is delimited by space or double quote

	the calling function should free word and replace 
	it with the returned new_word
*/
char	*ft_dollar_exps(char *word, t_token *env_lst)
{
	int		quote_state;
	int		i;
	char	*new_word;

	ft_init_local_var(word, &quote_state, &i, &new_word);
	if (!new_word)
		return (NULL);
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] && quote_state != 1)
		{
			new_word = ft_strjoin_1(new_word, &word, i - 1);
			if (!new_word)
				return (NULL);
			new_word = ft_strjoin_2(new_word, &word, env_lst);
			if (!new_word)
				return (NULL);
			i = 0;
		}
		else
			i++;
		quote_state = ft_set_quote_state(word[i], quote_state);
	}
	return (ft_strjoin_1(new_word, &word, i - 1));
}

/*
	do not expand if it's an heredoc
	iterate through the lst and apply word expansion to all token
	in case of error, return 1
	the calling function should delete the list
*/
int	ft_dollar_exps_lst(t_token *lst, t_token *env_lst)
{
	char	*exp_word;

	while (lst)
	{
		if (lst->prev && ft_strncmp(lst->prev->word, "<<", 3) == 0)
			;
		else
		{
			exp_word = ft_dollar_exps(lst->word, env_lst);
			if (!exp_word)
			{
				write(2, "exps fails\n", 11);
				return (1);
			}
			free(lst->word);
			lst->word = exp_word;
		}
		lst = lst->next;
	}
	return (0);
}
