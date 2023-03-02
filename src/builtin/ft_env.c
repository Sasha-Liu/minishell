/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:45:03 by sasha             #+#    #+#             */
/*   Updated: 2023/03/02 15:49:32 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(char **argv, t_shell *shell)
{
	t_token	*env;

	if (argv[1])
	{
		write(2, "env: invalid options\n", 21);
		return (1);
	}
	env = shell->env_lst;
	while (env)
	{
		write(1, env->word, ft_strlen(env->word));
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}
