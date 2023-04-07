/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:43:06 by sasha             #+#    #+#             */
/*   Updated: 2023/04/07 10:50:59 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
    Free the old env array and get a new one
*/
void	ft_update_env_array(t_shell *shell)
{	
	ft_free_env_array(&(shell->env_tab));
	if (ft_get_env_array(shell->env_lst, &(shell->env_tab)))
	{
		write(2, "malloc fails\n", 13);
		exit (1);
	}
	exit (0);
}
