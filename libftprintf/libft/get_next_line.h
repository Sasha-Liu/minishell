/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:40:54 by hsliu             #+#    #+#             */
/*   Updated: 2023/02/08 16:28:58 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# define BUFFER_SIZE 42
# define TRUE 1
# define FALSE 0

char	*get_next_line(int fd);
void	ft_trim(char **str, int eof);
char	*ft_give_line(char *str);
int		ft_read(int fd, char **str);
int		ft_init(char **str, int *eof);

#endif
