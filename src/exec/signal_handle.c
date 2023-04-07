/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:20:58 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/07 15:25:58 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parsing.h"

void	handle_ctrl_c(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 128 + signum;
}

void	handle_ctrl_c_exec(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	printf("\n");
	g_exit_status = 128 + signum;
	exit(g_exit_status);
}

void	handle_ctrl_d_exec(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	printf("Quit (core dumped)\n");
	g_exit_status = 128 + signum;
	exit(g_exit_status);
}

void	handle_ctrl_c_heredoc(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	printf("\n");
	g_exit_status = 128 + signum;
	exit(g_exit_status);
}
