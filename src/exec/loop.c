/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:55:13 by hsliu             #+#    #+#             */
/*   Updated: 2023/02/24 16:04:48 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
    return 1 when err
    normally never return
*/
int loop(void)
{
    t_shell shell;
    t_token	*lst_cmd;
	// t_cmd	*cmd;
    char    *buffer;

    if (ft_get_env(&(shell.env_lst)))
	{
		return (1);
	}
    while (1)
    {
        buffer = readline("minishell-> ");
        if (buffer == NULL)
            break ;
        if (*buffer == '\0')
            ;
        else if (ft_parsing(buffer, &shell))
		    write(2, "parsing fails\n", 14);
        else
        {
            add_history(buffer);
            lst_cmd = ft_get_lst_cmd(shell.parsed_input);
	        shell.nb_pipe = get_number_of_pipe(shell.parsed_input);
	        shell.env = get_array_env(shell.env_lst);
	        shell.cmd = ft_get_array_cmd(shell.parsed_input, shell.nb_pipe);
			// cmd = shell.cmd;
            // int	g = 0;
            // while (cmd->command)
            // {
            //     int	h = 0;
            //     while (cmd->command[h])
            //     {
            //         ft_printf("g = %d et cmd = %s\n", g, cmd->command[h]);
            //         h++;
            //     }
            //     cmd++;
            // }
            ft_exec(&shell);
            ft_delete_lst(&lst_cmd);
        }
        ft_delete_lst(&shell.parsed_input);
        *buffer = '\0';
        free(buffer);
    }
    ft_exit(&shell);
    return (1);
}