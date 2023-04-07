/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:10:25 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/07 16:35:09 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_init_command(t_token *lst, t_cmd *cmd, int size)
{
	t_token	*node;
	int		i;

	node = lst;
	i = 0;
	while (i < size)
	{
		if (ft_init_one(node, cmd + i))
		{
			write(2, "malloc fails\n", 13);
			return (1);
		}
		node = ft_next_cmd(node);
		while (node && ft_strcmp(node->word, "|") == 0 && node->is_op)
		{
			node = node->next;
			i++;
		}
		i++;
	}
	return (0);
}

/*
	node is the begin of a cmd
*/
int	ft_init_one(t_token *node, t_cmd *cmd)
{
	int		i;
	int		count;
	char	**args;

	i = 0;
	count = ft_count_args(node);
	if (count == 0)
	{
		cmd->args = NULL;
		return (0);
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
		return (1);
	while (i < count)
	{
		args[i] = node->word;
		node->word = NULL;
		node = node->next;
		i++;
	}
	args[i] = NULL;
	cmd->args = args;
	return (0);
}

/*
    count size of char **
	ex. ls -l will hve size 2
*/
int	ft_count_args(t_token *node)
{
	int	count;

	count = 0;
	while (1)
	{
		if (!node || (ft_strcmp(node->word, "|") == 0 && node->is_op))
			return (count);
		else
		{
			count++;
			node = node->next;
		}
	}
}

/*
    return a node that is start of next cmd, 
    return NULL if it's the last cmd in the lst 
*/
t_token	*ft_next_cmd(t_token *node)
{
	while (1)
	{
		if (node == NULL)
			return (NULL);
		else if (ft_strcmp(node->word, "|") == 0 && node->is_op)
			return (node->next);
		else
			node = node->next;
	}
}
