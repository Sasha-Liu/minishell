/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:15:53 by sasha             #+#    #+#             */
/*   Updated: 2023/04/10 16:14:16 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	ft_add_to_lst(t_token **env_lst, t_token *var);

/*
	can take multiple args
	each has form name=value
	equal sign cannot be a name
*/
int	ft_export(char **argv, t_shell *shell)
{
	int		ret;
	int		i;
	t_token	*var;

	if (argv[1] == NULL)
	{
		write(2, "no argument\n", 13);
		return (1);
	}
	ret = 0;
	i = 1;
	while (argv[i])
	{
		if (ft_illegal_name(argv[i]))
			ret = 1;
		else if (ft_strchr(argv[i], '='))
		{
			var = ft_new_token(argv[i], ft_strlen(argv[i]));
			if (var)
				ft_add_to_lst(&(shell->env_lst), var);
		}
		i++;
	}
	ft_update_env_array(shell);
	return (ret);
}

/*
	search if the env var already exist,
	if it exist, remove the old token and put the new one in place
	otherwise, append it at the end
*/
static void	ft_add_to_lst(t_token **env_lst, t_token *var)
{
	int		name_len;
	t_token	*node;
	t_token	*prev;
	t_token	*next;

	name_len = ft_name_len(var->word);
	node = *env_lst;
	while (node && ft_strncmp(node->word, var->word, name_len))
		node = node->next;
	if (node == NULL)
		return (ft_add_token(env_lst, var));
	prev = node->prev;
	next = node->next;
	var->next = next;
	if (next)
		next->prev = var;
	if (node == *env_lst)
		*env_lst = var;
	else
	{
		prev->next = var;
		var->prev = prev;
	}
	ft_delete_token(&node);
}

/*
	count the length of the part before '='
	if there is not = present in the str, it will return the whole length
*/
int	ft_name_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	check_equal(char *name)
{
	if (name[0] == '=')
	{
		write(2, "bash: export: `", 16);
		write(2, name, ft_strlen(name));
		write(2, "': not a valid identifier\n", 27);
		return (1);
	}
	return (0);
}

/*
	name can only cantains alphabet, number and underscore
	name cannot begin with number
	if name doesn't end with '=', ignore it
*/

int	ft_illegal_name(char *name)
{
	int	i;

	if (check_equal(name) == 1)
		return (1);
	if (ft_isdigit(name[0]))
	{
		write(2, "not a valid identifier\n", 24);
		return (1);
	}
	i = 0;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			write(2, "not a valid identifier\n", 24);
			return (1);
		}
		i++;
	}
	return (0);
}
