/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:51:12 by hsliu             #+#    #+#             */
/*   Updated: 2023/03/02 13:53:38 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include "builtin.h"
# include "signal.h"

void	ft_print_lst(t_token *lst);
void	ft_print_cmd(t_cmd *cmd, int size);

#endif