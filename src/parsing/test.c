/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:00:28 by sasha             #+#    #+#             */
/*   Updated: 2023/03/01 21:07:23 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

void	ft_print_lst(t_token *lst)
{
	if (!lst)
	{
		printf("lst empty\n");
	}
	while (lst)
	{
		printf("%s -> ", lst->word);
		lst = lst->next;
	}
}

void	ft_print_cmd(t_cmd *cmd, int size)
{
	int	i;
	int	j;

	i = 0;
	printf("size: %d\n", size);
	while (i < size)
	{
		printf("cmd %d: ", i);
		j = 0;
		while (cmd[i].args && cmd[i].args[j])
		{
			printf("_%s_", cmd[i].args[j]);
			j++;
		}
		printf("\n");
		printf("read_file %s \n", cmd[i].read_file);
		printf("write_file %s \n", cmd[i].write_file);
		printf("append_file %s \n", cmd[i].append_file);
		i++;
	}
	printf("\n");
}


int main()
{
	t_shell shell;
    char    *buffer;

    if (ft_get_env(&shell))
	{
		return (1);
	}
    while (1)
    {
        buffer = readline("minishell-> ");
        if (buffer == NULL)
            break ;
        if (ft_parsing(buffer, &shell))
		    write(2, "parsing fails\n", 14);
        else
        {
            add_history(buffer);
			ft_print_cmd(shell.cmd, shell.cmd_size);
        }
        ft_free_cmd(shell.cmd, shell.cmd_size);
		shell.cmd = NULL;
        *buffer = '\0';
        free(buffer);
    }
    ft_exit(&shell);
    return (1);
}

