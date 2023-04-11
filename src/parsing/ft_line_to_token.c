/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_to_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:36:25 by sasha             #+#    #+#             */
/*   Updated: 2023/04/11 12:30:52 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_err_mess(void);

t_token	*ft_line_to_token(char *buffer)
{
	t_token	*lst;
	t_token	*token;

	lst = NULL;
	while (*buffer)
	{
		while (*buffer == ' ')
			buffer++;
		if (*buffer == '\0')
			break ;
		token = ft_get_token(&buffer);
		if (!token)
		{
			return (ft_delete_lst(&lst), NULL);
		}
		ft_add_token(&lst, token);
	}
	return (lst);
}

/*
	check the lst for syntax error
	for example:
	cmd1 | cmd2 | (missing cmd)
	| cmd1 | cmd2 (missing cmd)
	cmd > (missing outfput file)
	cmd < (missing input file)
	the function will check the token after the operator,
	if the token after is also an operator,
	then there's an syntax error
	otherwise, the word will be taken as filename or cmd
	Note: command like
	cmd | cmd | > outfile 
	is valid in bash
*/
int	ft_syntax_err(t_token *lst)
{
	if (lst == NULL)
		return (0);
	if (ft_is_pipe(lst->word))
		return (ft_err_mess());
	while (lst->next)
	{
		if (ft_is_redirection(lst->word) && ft_is_operator(lst->next->word))
			return (ft_err_mess());
		if (ft_is_pipe(lst->word) && ft_is_pipe(lst->next->word))
			return (ft_err_mess());
		lst = lst->next;
	}
	if (ft_is_operator(lst->word))
		return (ft_err_mess());
	return (0);
}

static int	ft_err_mess(void)
{
	g_exit_status = 2;
	write(2, "syntax error\n", 13);
	return (1);
}

/*
	return the next token
	In case of error return NULL, ex:
    if malloc fails
    if quote not enclosed
*/
t_token	*ft_get_token(char **buffer)
{
	t_token	*token;
	int		length;

	token = NULL;
	if (ft_is_operator(*buffer))
	{
		length = ft_is_operator(*buffer);
		token = ft_is_token(buffer, length);
		token->is_op = 1;
	}
	else if (ft_is_word(*buffer))
	{
		length = ft_is_word(*buffer);
		if (length == -1)
		{
			g_exit_status = 2;
			write(2, "quote not enclosed\n", 19);
			return (NULL);
		}
		token = ft_is_token(buffer, length);
		token->is_op = 0;
	}
	return (token);
}

/*
	calling this function will return the token 
	of buffer[0 ... length - 1]
	buffer pointer will advance accordingly
	return NULL if malloc fails
*/
t_token	*ft_is_token(char **buffer, int length)
{
	t_token	*token;

	token = ft_new_token(*buffer, length);
	(*buffer) = (*buffer) + length;
	return (token);
}
