/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:43:58 by sasha             #+#    #+#             */
/*   Updated: 2023/04/11 12:17:56 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
	this function can only be called if there is pipe involved
	cmd is an array of size n, p is an array of 2n - 2
	the function will use dup
*/
void	ft_set_pipe(t_cmd *cmd, int n, int *p)
{
	int	i;

	cmd[0].write_fd = dup(p[1]);
	close(p[1]);
	i = 1;
	while (i < n - 1)
	{
		cmd[i].read_fd = dup(p[2 * (i - 1)]);
		cmd[i].write_fd = dup(p[i * 2 + 1]);
		close(p[2 * (i - 1)]);
		close(p[i * 2 + 1]);
		i++;
	}
	cmd[n - 1].read_fd = dup(p[2 * n - 4]);
	close(p[2 * n - 4]);
}

/*
	malloc an array of size 2n and called pipe on every two element
	array[0  1]
	array[2  3]
	...
	array[2n-2 2n-1]
*/
int	*ft_malloc_pipe(int n)
{
	int	*p;
	int	i;

	p = malloc(sizeof(int) * n * 2);
	if (!p)
	{
		write(2, "malloc fails\n", 13);
		return (NULL);
	}
	i = 0;
	while (i < 2 * n)
	{
		if (pipe(p + i))
		{
			write(2, "pipe fails\n", 11);
			ft_close_pipe_err(p, i);
			free(p);
			return (NULL);
		}
		i = i + 2;
	}
	return (p);
}

/*
	This function close all the pipe 
	from p[i - 1] down to p[0]
*/
void	ft_close_pipe_err(int *p, int i)
{
	i--;
	while (i >= 0)
	{
		close(p[i]);
		i--;
	}
}

/*
	count how many | are there in the lst
*/
int	ft_count_pipe(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (ft_strncmp(lst->word, "|", 1) == 0 && lst->is_op)
			i++;
		lst = lst->next;
	}
	return (i);
}
