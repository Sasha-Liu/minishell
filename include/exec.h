/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:51:12 by hsliu             #+#    #+#             */
/*   Updated: 2023/04/07 12:17:51 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include "builtin.h"
# include "signal.h"

# include <errno.h>
# include <signal.h>

void	ft_print_lst(t_token *lst);
void	ft_print_cmd(t_cmd *cmd, int size);

int		exec(t_shell *shell);

//define cmd path
int		direct_path(char **cmd);
int		find_path(char **cmd, char **envp);

int		launch(t_shell *shell, int i);

int		ft_dup(t_shell *shell, int i);
int		ft_open(t_cmd *cmd);

void	close_pipe(t_shell *shell, int nb);
int		close_all(t_shell *shell);

void	error_cmd(char *cmd);

int		builtin(t_shell *shell, int i, int status);

void	set_interactive_signals(void);
void	set_exec_signals(void);
void	set_heredoc_signals(void);
void	unplug_signals(void);

void	handle_ctrl_c(int signum, siginfo_t *info, void *context);
void	handle_ctrl_c_heredoc(int signum, siginfo_t *info, void *context);
void	handle_ctrl_c_exec(int signum, siginfo_t *info, void *context);
void	handle_ctrl_d_exec(int signum, siginfo_t *info, void *context);

#endif