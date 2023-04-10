/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:09:04 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/10 14:15:34 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"
#include "builtin.h"

int	check_builtin(t_shell *shell, int i)
{
	if (shell->cmd[0].args == NULL)
		return (0);
	if (ft_strcmp(shell->cmd[i].args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(shell->cmd[i].args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(shell->cmd[i].args[0], "export") == 0)
		return (1);
	if (ft_strcmp(shell->cmd[i].args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(shell->cmd[i].args[0], "env") == 0)
		return (1);
	if (ft_strcmp(shell->cmd[i].args[0], "exit") == 0)
		return (1);
	return (0);
}

int	builtin(t_shell *shell, int i, int status)
{
	int	tmp;

	tmp = 0;
	if (ft_strcmp(shell->cmd[i].args[0], "echo") == 0)
		tmp = ft_echo(shell->cmd[i].args);
	if (ft_strcmp(shell->cmd[i].args[0], "cd") == 0)
		tmp = ft_cd(shell->cmd[i].args, shell);
	if (ft_strcmp(shell->cmd[i].args[0], "pwd") == 0)
		tmp = ft_pwd(shell->cmd[i].args);
	if (ft_strcmp(shell->cmd[i].args[0], "export") == 0)
		tmp = ft_export(shell->cmd[i].args, shell);
	if (ft_strcmp(shell->cmd[i].args[0], "unset") == 0)
		tmp = ft_unset(shell->cmd[i].args, shell);
	if (ft_strcmp(shell->cmd[i].args[0], "env") == 0)
		tmp = ft_env(shell->cmd[i].args, shell);
	if (ft_strcmp(shell->cmd[i].args[0], "exit") == 0)
		ft_exit(shell->cmd[i].args, shell);
	if (status == 1)
	{
		clear_history();
		ft_delete_lst(&(shell->env_lst));
		ft_free_cmd(shell->cmd, shell->cmd_size);
		ft_free_env_array(&(shell->env_tab));
	}
	return (tmp);
}
