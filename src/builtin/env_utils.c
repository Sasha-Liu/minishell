/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:43:06 by sasha             #+#    #+#             */
/*   Updated: 2023/04/07 13:38:43 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
    Free the old env array and get a new one
*/
int	ft_update_env_array(t_shell *shell)
{	
	ft_free_env_array(&(shell->env_tab));
	if (ft_get_env_array(shell->env_lst, &(shell->env_tab)))
	{
		write(2, "malloc fails\n", 13);
		return (1);
	}
	return (0);
}
