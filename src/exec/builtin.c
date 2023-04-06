/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:09:04 by pchapuis          #+#    #+#             */
/*   Updated: 2023/03/29 16:46:36 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"
#include "builtin.h"

void	builtin(t_shell *shell, int i)
{
	if (ft_strcmp(shell->cmd[i].args[0], "echo") == 0)
		ft_echo(shell->cmd[i].args);
	if (ft_strcmp(shell->cmd[i].args[0], "cd") == 0)
		ft_cd(shell->cmd[i].args, shell);
	if (ft_strcmp(shell->cmd[i].args[0], "pwd") == 0)
		ft_pwd(shell->cmd[i].args);
	if (ft_strcmp(shell->cmd[i].args[0], "export") == 0)
		ft_export(shell->cmd[i].args, shell);
	if (ft_strcmp(shell->cmd[i].args[0], "unset") == 0)
		ft_unset(shell->cmd[i].args, shell);
	if (ft_strcmp(shell->cmd[i].args[0], "env") == 0)
		ft_env(shell->cmd[i].args, shell);
	if (ft_strcmp(shell->cmd[i].args[0], "exit") == 0)
		ft_exit(shell->cmd[i].args, shell);
}
