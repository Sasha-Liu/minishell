/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:45:02 by sasha             #+#    #+#             */
/*   Updated: 2023/02/09 13:16:47 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
    combine new and old[0 .. n] to create res
	new is then free, while res is returned
	char **old is advanced accordingly
*/
char	*ft_strjoin_1(char *new_word, char **old, int n)
{
	int		new_len;
	char	*res;
	int		i;

	if (n < 0)
		return (new_word);
	new_len = ft_strlen(new_word);
	res = malloc(sizeof(char) * new_len + n + 2);
	if (!res)
		return (free(new_word), NULL);
	i = 0;
	while (new_word[i])
	{
		res[i] = new_word[i];
		i++;
	}
	while (i < new_len + n + 1)
	{
		res[i] = **old;
		(*old)++;
		i++;
	}
	res[i] = '\0';
	return (free(new_word), res);
}

/*
	old start with $ and have at least one char after it
	if $key does not exist in env_lst, 
	$key is expansioned to empty string
*/
char	*ft_strjoin_2(char *new_word, char **old, t_token *env_lst)
{
	int		key_len;
	char	*search_key;
	char	*para;
	char	*res;

	key_len = ft_delimit_dollar(*old);
	search_key = ft_add_equal(*old);
	if (!search_key)
	{
		free(new_word);
		return (NULL);
	}
	para = ft_get_para(search_key, env_lst);
	(*old) = (*old) + key_len;
	if (para == NULL)
		return (free(search_key), new_word);
	res = ft_strjoin(new_word, para);
	if (!res)
		write(2, "malloc fails\n", 13);
	return (free(search_key), free(new_word), res);
}

/*
	the function will count until it meets a delimiter
	a delimiter is a space, double quote, single quote or null
	if key is $TEST(space)SOMETHINGELSE, return 5
	if key is $PWD(space)SOMETHINGELSE, return 4
	if key is $PWD(double quote)SOMETHINGELSE, return 4
*/
int	ft_delimit_dollar(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == ' ' || key[i] == '"' || key[i] == '\'')
			return (i);
		i++;
	}
	return (i);
}

/*
	return a key with dollar sign removed 
	and add equal sign 
*/
char	*ft_add_equal(char *key)
{
	int		i;
	int		n;
	char	*new_key;

	n = ft_delimit_dollar(key);
	new_key = malloc(sizeof(char) * (n + 1));
	if (!new_key)
	{
		write(2, "malloc fails\n", 13);
		return (NULL);
	}
	key++;
	i = 0;
	while (i < n - 1)
	{
		new_key[i] = key[i];
		i++;
	}
	new_key[i] = '=';
	new_key[i + 1] = '\0';
	return (new_key);
}

/*
	return the pointer to the corresponding key value
	return NULL when nothing is found
	the pointer that is returned should NOT be free
	since it's a part of the env_lst
	note:
	search key is key plus equal sign and 
	dollar sign removed, ex: key=
*/
char	*ft_get_para(char *search_key, t_token *env_lst)
{
	int		len;

	len = ft_strlen(search_key);
	while (env_lst)
	{
		if (ft_strncmp(env_lst->word, search_key, len) == 0)
		{
			return (env_lst->word + len);
		}
		env_lst = env_lst->next;
	}
	return (NULL);
}
