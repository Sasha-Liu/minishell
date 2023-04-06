/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:18:07 by sasha             #+#    #+#             */
/*   Updated: 2023/04/06 15:12:23 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_cd_home(t_shell *shell);
static int	ft_update_pwd(t_shell *shell, char *dir);
static int	ft_count_args_cd(char **argv);

int	ft_cd(char **argv, t_shell *shell)
{
	if (ft_count_args_cd(argv) >= 3)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (argv[1] == NULL)
	{
		if (ft_cd_home(shell))
			return (1);
		return (0);
	}
	if (chdir(argv[1]))
	{
		perror("chdir");
		return (1);
	}
	if (ft_update_pwd(shell, argv[1]))
	{
		return (1);
	}
	return (0);
}

static int	ft_count_args_cd(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

/*
	if return NULL
	it means the HOME is unset
	the returned pointer cannot be freed
*/
static int	ft_cd_home(t_shell *shell)
{
	t_token	*env_lst;
	char	*home;

	write(2, "cd_home\n", 8);
	home = NULL;
	env_lst = shell->env_lst;
	while (env_lst)
	{
		if (ft_strncmp("HOME=", env_lst->word, 5) == 0)
			home = env_lst->word + 5;
		env_lst = env_lst->next;
	}
	if (home == NULL)
	{
		write(2, "cd: HOME is unset\n", 18);
		return (1);
	}
	if (chdir(home))
	{
		//write(2, home, 10);
		perror("chdir");
		return (1);
	}
	if (ft_update_pwd(shell, home))
	{
		return (1);
	}
	return (0);
}

/*
	update PWD
*/
static int	ft_update_pwd(t_shell *shell, char *dir)
{
	t_token	*env_lst;
	char	*word;

	word = ft_strjoin("PWD=", dir);
	if (word == NULL)
	{
		write(2, "malloc fails\n", 13);	
		return (1);
	}
	env_lst = shell->env_lst;
	while(env_lst)
	{
		if (ft_strncmp(env_lst->word, "PWD=", 4) == 0)
		{
			free(env_lst->word);
			env_lst->word = word;
			return (0);
		}
		env_lst = env_lst->next;
	}
	free(word);
	return (0);
}
