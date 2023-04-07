/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:28 by sasha             #+#    #+#             */
/*   Updated: 2023/04/07 11:15:27 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
	if first malloc to get env_lst fails, abort
	if the second malloc fails, continue to execute 
*/
int	ft_init_shell(t_shell *shell)
{
	if (ft_get_env_lst(&(shell->env_lst)))
	{
		write(2, "malloc fails\n", 13);
		return (1);
	}
	if (ft_get_env_array(shell->env_lst, &(shell->env_tab)))
	{
		write(2, "malloc fails\n", 13);
		return (0);
	}
	shell->cmd = NULL;
	shell->cmd_size = 0;
	g_exit_status = 0;
	return (0);
}

/*
	env_lst is for output
	in case of error, the function return 1 and free the env_lst
*/
int	ft_get_env_lst(t_token **env_lst)
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

int	ft_get_env_array(t_token *env_lst, char ***env)
{
	int		i;
	int		len;
	char	**tab;
	t_token	*node;

	node = env_lst;
	len = ft_lstlen(env_lst);
	tab = malloc(sizeof(char *) * (len + 1));
	*env = NULL;
	if (tab == NULL)
		return (1);
	i = 0;
	while (i < len)
	{
		tab[i] = ft_strdup(node->word);
		if (tab[i] == NULL)
		{
			return (ft_free_env_array(&tab), 1);
		}
		node = node->next;
		i++;
	}
	tab[i] = NULL;
	*env = tab;
	return (0);
}

/*
	free the char ** env array
*/
void	ft_free_env_array(char ***env)
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
