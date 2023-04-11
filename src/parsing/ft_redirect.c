/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:19:25 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/11 15:57:07 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
	cmd is an array of length 'size' 
*/
void	ft_redirect(t_token **lst, t_cmd *cmd, int size, t_shell *shell)
{
	int		i;
	t_token	*node;

	node = *lst;
	i = 0;
	while (i < size)
	{
		node = ft_redirect_one(node, cmd + i, shell);
		if (node)
			node = node->next;
		i++;
	}
	ft_delete_redirect_lst(lst);
}

t_token	*ft_redirect_one(t_token *node, t_cmd *cmd, t_shell *shell)
{
	while (1)
	{
		if (node == NULL)
			return (NULL);
		if (node->word == NULL)
			node = node->next;
		if (node == NULL || (ft_strncmp(node->word, "|", 2) == 0
				&& node->is_op))
			return (node);
		if (!ft_strcmp(node->word, "<<") && node->is_op)
		{
			if (cmd->read_fd != STDIN_FILENO)
				close(cmd->read_fd);
			cmd->read_fd = ft_here_doc(node->next->word, shell);
		}
		else if (((!ft_strcmp(node->word, ">") || !ft_strcmp(node->word, ">>")
					|| !ft_strcmp(node->word, "<")) && node->is_op))
		{
			ft_update_file(node, cmd);
		}	
		node = node->next;
	}
}

void	ft_update_file(t_token *node, t_cmd *cmd)
{
	char	*file;
	char	*op;

	op = node->word;
	file = node->next->word;
	if (ft_strcmp(op, "<") == 0)
	{
		free(cmd->read_file);
		cmd->read_file = file;
	}
	else if (ft_strcmp(op, ">") == 0)
	{
		free(cmd->write_file);
		cmd->write_file = file;
	}
	else if (ft_strcmp(op, ">>") == 0)
	{
		free(cmd->append_file);
		cmd->append_file = file;
	}
	else
	{
		return ;
	}
	node->next->word = NULL;
}

void	ft_delete_redirect_lst(t_token **lst)
{
	t_token	*node;

	node = *lst;
	while (node && node->next)
	{
		if ((!ft_strcmp(node->word, "<") || !ft_strcmp(node->word, "<<")
				|| (!ft_strcmp(node->word, ">")
					|| !ft_strcmp(node->word, ">>")))
			&& node->is_op)
		{
			node = ft_delete_redirect_node(node);
		}
		else
		{
			node = node->next;
		}
	}
	while (node && node->prev)
	{
		node = node->prev;
	}
	*lst = node;
}

/*
	delete '> file' or '< file' etc
	always delete two consecutive node
*/
t_token	*ft_delete_redirect_node(t_token *node1)
{
	t_token	*prev;
	t_token	*node2;
	t_token	*next;

	prev = node1->prev;
	node2 = node1->next;
	next = node1->next->next;
	free(node1->word);
	free(node1);
	free(node2->word);
	free(node2);
	if (prev)
	{
		prev->next = next;
	}
	if (next)
	{
		next->prev = prev;
	}
	if (next == NULL)
	{
		return (prev);
	}
	return (next);
}
