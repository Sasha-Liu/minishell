/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_status_exp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:05:35 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/10 15:34:47 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
	Expend $? to exit status
	Ex	$? -> 0
	 	string$?string -> string0string
*/
char	*ft_exit_exps_node(char *word)
{
	int		quote_state;
	int		i;
	char	*new_word;

	ft_init_local_var(word, &quote_state, &i, &new_word);
	if (!new_word)
		return (NULL);
	while (word[i])
	{
		if (ft_strncmp(word + i, "$?", 2) == 0 && quote_state != 1)
		{
			new_word = ft_strjoin_1(new_word, &word, i - 1);
			if (!new_word)
				return (NULL);
			new_word = ft_strjoin_3(new_word, &word);
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
*/
int	ft_exit_exps_lst(t_token *lst)
{
	char	*exp_word;

	while (lst)
	{
		if (lst->prev && ft_strncmp(lst->prev->word, "<<", 3) == 0)
			;
		else
		{
			exp_word = ft_exit_exps_node(lst->word);
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

/*
	old start with $?
	exit status is append to new word
	old is advanced accordingly
	g_exit_status is a global variable
*/
char	*ft_strjoin_3(char *new_word, char **old)
{
	char	*res;
	char	*exit_str;

	exit_str = ft_itoa(g_exit_status);
	if (exit_str == NULL)
	{
		write(2, "malloc fails\n", 13);
		free(new_word);
		return (NULL);
	}
	res = ft_strjoin(new_word, exit_str);
	if (res == NULL)
	{
		write(2, "malloc fails\n", 13);
		free(new_word);
		free(exit_str);
		return (NULL);
	}
	*old = *old + 2;
	free(new_word);
	free(exit_str);
	return (res);
}
