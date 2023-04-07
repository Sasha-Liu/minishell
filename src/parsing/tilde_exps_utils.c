/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_exps_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:51:18 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/07 10:35:20 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
    if it is a simple tilde or tilde slash, it's replaced with the $HOME
    if it has the form ~LOGIN or ~LOGIN/, 
    it's replaced with the content in /etc/passwd
    if LOGIN does not exist, nothing is changed
    if word does not begin with tilde, nothing is change
	if HOME is unset, nothing is changed
*/
char	*ft_tilde_exps(char *word, t_token *env_lst)
{
	char	*home;

	home = ft_get_home(env_lst);
	if (ft_strncmp(word, "~", 2) == 0)
	{
		return (ft_case_tilde(word, home));
	}
	if (ft_strncmp(word, "~/", 2) == 0)
	{
		return (ft_case_tilde_slash(word, home));
	}
	else
	{
		return (ft_case_tilde_login(word));
	}
}

char	*ft_case_tilde_login(char *word)
{
	char	*res;
	char	*home;

	home = ft_get_homedir(word);
	if (!home)
	{
		res = ft_strdup(word);
		if (!res)
		{
			write(2, "malloc fails\n", 13);
		}
		return (res);
	}
	res = ft_strjoin(home, word + ft_delimit_login(word));
	if (!res)
	{
		write(2, "malloc fails\n", 13);
	}
	return (res);
}

char	*ft_case_tilde_slash(char *word, char *home)
{
	char	*res;

	if (home == NULL)
	{
		res = ft_strdup(word);
		if (!res)
		{
			write(2, "malloc fails\n", 13);
		}
		return (res);
	}
	res = ft_strjoin(home, word + 1);
	if (!res)
	{
		write(2, "malloc fails\n", 13);
	}
	return (res);
}

char	*ft_case_tilde(char *word, char *home)
{
	char	*res;

	if (home == NULL)
	{
		res = ft_strdup(word);
		if (!res)
		{
			write(2, "malloc fails\n", 13);
		}
		return (res);
	}
	res = ft_strdup(home);
	if (!res)
	{
		write(2, "malloc fails\n", 13);
	}
	return (res);
}

/*
	if HOME=/home/user
	return pointer to /home/user
	if HOME is unset
	return NULL
*/
char	*ft_get_home(t_token *env_lst)
{
	while (env_lst)
	{
		if (ft_strncmp(env_lst->word, "HOME=", 5) == 0)
			return (env_lst->word + 5);
		env_lst = env_lst->next;
	}
	return (NULL);
}
