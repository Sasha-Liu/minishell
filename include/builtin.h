/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:05:27 by sasha             #+#    #+#             */
/*   Updated: 2023/04/10 14:15:49 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parsing.h"

/*
    check if the argv have to be freed 
*/
int		ft_echo(char **argv);
int		ft_cd(char **argv, t_shell *shell);
int		ft_pwd(char **argv);
int		ft_export(char **argv, t_shell *shell);
int		ft_unset(char **argv, t_shell *shell);
int		ft_env(char **argv, t_shell *shell);

void	ft_exit(char **argv, t_shell *shell);
void	ft_exit_standart(t_shell *shell);
void	ft_exit_without_free(t_shell *shell);

int		ft_illegal_name(char *name);
int		ft_name_len(char *str);

/*	utils	*/
int		ft_update_env_array(t_shell *shell);

#endif
