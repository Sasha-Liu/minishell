/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:35:34 by pchapuis          #+#    #+#             */
/*   Updated: 2023/04/07 15:26:01 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "exec.h"

void	set_interactive_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	sa.sa_sigaction = handle_ctrl_c;
	sigaction(SIGINT, &sa, NULL);
}

void	set_exec_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sa.sa_sigaction = handle_ctrl_c_exec;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_sigaction = handle_ctrl_d_exec;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sa.sa_sigaction = handle_ctrl_c_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

void	unplug_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
