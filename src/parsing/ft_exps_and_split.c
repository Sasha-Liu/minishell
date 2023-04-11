/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exps_and_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:43:52 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/10 16:23:25 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
    if it's a heredoc, remove only quote, don't expand
*/
int	ft_exps_and_split(t_token **lst, t_token *env_lst)
{
	if (ft_exit_exps_lst(*lst))
	{
		return (1);
	}
	if (ft_dollar_exps_lst(*lst, env_lst))
	{
		return (1);
	}
	if (ft_tilde_exps_lst(*lst, env_lst))
	{
		return (1);
	}
	if (ft_syntax_err_2(*lst))
	{
		return (1);
	}
	if (ft_split_lst(lst))
	{
		return (1);
	}
	ft_rm_quote_lst(*lst);
	return (0);
}

/*
    check if rediretion file will be splitted into multiword
    or after expansion, 
    does the word following redirection contain unquoted space 
*/
int	ft_syntax_err_2(t_token *lst)
{
	int	err;

	err = 0;
	while (lst)
	{
		if (lst->prev && ft_strncmp(lst->prev->word, ">>", 3) == 0)
			err = ft_exist_unquoted_space(lst->word);
		else if (lst->prev && ft_strncmp(lst->prev->word, ">", 2) == 0)
			err = ft_exist_unquoted_space(lst->word);
		else if (lst->prev && ft_strncmp(lst->prev->word, "<", 2) == 0)
			err = ft_exist_unquoted_space(lst->word);
		if (err == 1)
		{
			g_exit_status = 1;
			write(2, "ambiguous redirection\n", 22);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

/*
	return a non zero number if the word contains unquoted space
*/
int	ft_exist_unquoted_space(char *word)
{
	int	i;
	int	quote_state;

	i = 0;
	quote_state = ft_set_quote_state(word[0], 0);
	while (word[i])
	{
		if (word[i] == ' ' && quote_state == 0)
			return (1);
		i++;
		quote_state = ft_set_quote_state(word[i], quote_state);
	}
	return (0);
}
