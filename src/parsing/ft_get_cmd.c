/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:34:57 by sasha             #+#    #+#             */
/*   Updated: 2023/03/02 16:54:16 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_free_args(t_cmd *cmd);

/*
	malloc cmd according to how many pipe counted in the lst
	with write_fd and read_fd all init and connected by pipe
*/
t_cmd	*ft_get_cmd(t_token *lst, int *size)
{
	int		*p;
	t_cmd	*cmd;
	int		n;

	n = ft_count_pipe(lst);
	*size = n + 1;
	cmd = ft_malloc_cmd(n + 1);
	if (n == 0)
	{
		return (cmd);
	}
	if (n > 0)
	{
		p = ft_malloc_pipe(n);
		if (p == NULL || cmd == NULL)
		{
			return (free(cmd), free(p), NULL);
		}
		ft_set_pipe(cmd, n + 1, p);
		free(p);
	}
	return (cmd);
}

/*
	malloc n cmd and init the fd to stdin and stdout
*/
t_cmd	*ft_malloc_cmd(int n)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd) * n);
	if (!cmd)
	{
		write(2, "malloc fails\n", 13);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		cmd[i].args = NULL;
		cmd[i].read_file = NULL;
		cmd[i].write_file = NULL;
		cmd[i].append_file = NULL;
		cmd[i].read_fd = 0;
		cmd[i].write_fd = 1;
		cmd[i].child_pid = 0;
		cmd[i].exit_status = 0;
		i++;
	}
	return (cmd);
}

void	ft_free_cmd(t_cmd *cmd, int size)
{
	int	i;

	if (cmd == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		if (cmd[i].args == NULL)
			;
		else
		{
			ft_free_args(cmd + i);
			free(cmd[i].args);
			free(cmd[i].read_file);
			free(cmd[i].write_file);
			free(cmd[i].append_file);
		}
		i++;
	}
	free(cmd);
}

static void	ft_free_args(t_cmd *cmd)
{
	int		i;
	char	**args;

	i = 0;
	args = cmd->args;
	if (args == NULL)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	cmd->args = NULL;
}
