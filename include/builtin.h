/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:05:27 by sasha             #+#    #+#             */
/*   Updated: 2023/03/01 20:31:13 by sasha            ###   ########.fr       */
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
void	ft_exit(t_shell *shell);

int     ft_illegal_name(char *name);
int	    ft_name_len(char *str);

/*	utils	*/
void    ft_update_env_array(t_shell *shell);


#endif
