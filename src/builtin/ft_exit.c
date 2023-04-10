/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:58:31 by sasha             #+#    #+#             */
/*   Updated: 2023/04/10 14:15:44 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i ++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i ++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i ++;
	while (str[i] && str[i] == ' ')
		i ++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	ft_exit(char **argv, t_shell *shell)
{
	write(2, "exit\n", 6);
	if (argv[1] != NULL)
	{
		if (is_valid(argv[1]) == 0)
		{
			write(2, "bash: exit: ", 13);
			write(2, argv[1], ft_strlen(argv[1]));
			write(2, ": numeric argument required\n", 29);
			g_exit_status = 2;
		}
		else if (argv[2] != NULL)
		{
			write(2, "bash: exit: too many arguments\n", 32);
			g_exit_status = 1;
			return ;
		}
		else
			g_exit_status = ft_atoi(argv[1]);
	}
	clear_history();
	ft_delete_lst(&(shell->env_lst));
	ft_free_env_array(&(shell->env_tab));
	ft_free_cmd(shell->cmd, shell->cmd_size);
	exit(g_exit_status);
}

void	ft_exit_standart(t_shell *shell)
{
	clear_history();
	ft_delete_lst(&(shell->env_lst));
	ft_free_cmd(shell->cmd, shell->cmd_size);
	ft_free_env_array(&(shell->env_tab));
	exit(g_exit_status);
}

void	ft_exit_without_free(t_shell *shell)
{
	write(2, "exit\n", 6);
	clear_history();
	ft_delete_lst(&(shell->env_lst));
	ft_free_cmd(shell->cmd, shell->cmd_size);
	ft_free_env_array(&(shell->env_tab));
	exit(g_exit_status);
}
