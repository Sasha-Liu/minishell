/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:05:27 by sasha             #+#    #+#             */
/*   Updated: 2023/02/23 17:25:10 by hsliu            ###   ########.fr       */
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

#endif
