/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:28 by sasha             #+#    #+#             */
/*   Updated: 2023/03/01 12:46:05 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
	env_lst is for output
	in case of error, the function return 1 and free the env_lst
*/
int	ft_get_env(t_token **env_lst)
{
	extern char	**environ;
	t_token		*token;
	int			i;

	*env_lst = NULL;
	i = 0;
	while (environ[i])
	{
		token = ft_new_token(environ[i], ft_strlen(environ[i]));
		if (!token)
		{
			return (ft_delete_lst(env_lst), 1);
		}
		ft_add_token(env_lst, token);
		i++;
	}
	return (0);
}

/*
int	ft_get_env_2(t_token *env_lst, char ***env)
{
	
}

void	ft_free_env(char ***env)
{
	char	**tab;
	int		i;

	tab = *env;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	*env = NULL;
}

*/
