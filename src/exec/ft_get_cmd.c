#include "parsing.h"
#include "minishell.h"
#include "exec.h"

t_token	*ft_get_lst_cmd(t_token	*lst)
{
	int			i;
	t_token	*new_token;
	t_token	*lst_cmd;
	t_token *buffer;

	i = 0;
	lst_cmd = NULL;
	while (lst)
	{
		if (lst && lst->is_op)
		{
			if (ft_strncmp(lst->word, "|", 1) == 0)
			{
				new_token = ft_new_token(lst->word, ft_strlen(lst->word));
				ft_add_token(&lst_cmd, new_token);
				lst = lst->next;
			}
			else
			{
				lst = lst->next;
				lst = lst->next;
			}
		}
		while (lst && lst->is_op != 1)
		{
			if (i == 0)
			{
				new_token = ft_new_token(lst->word, ft_strlen(lst->word));
				buffer = new_token;
				ft_add_token(&lst_cmd, new_token);
				i++;
			}
			else
			{
				lst_cmd->next = ft_new_token(lst->word, ft_strlen(lst->word));
				lst_cmd = lst_cmd->next;
			}
			lst = lst->next;
		}
	}
	return (buffer);
}

t_cmd	*ft_get_array_cmd(t_token *lst, int nb_cmd)
{
	int		j;
	int		nb_arg;
	t_cmd	*cmd;
	t_cmd	*buffer_cmd;
	t_token	*buffer;

	buffer = lst;
	cmd = malloc(sizeof(t_cmd) * (nb_cmd + 1));
	buffer_cmd = cmd;
	while (lst)
	{
		j = 0;
		nb_arg = 0;
		while (buffer)
		{
			if (ft_strcmp(buffer->word, "|") == 0)
				break ;
			else if (buffer->is_op > 0)
				buffer = buffer->next;
			else if (buffer->is_op == 0)
				nb_arg++;
			buffer = buffer->next;
		}
		if (buffer)
			buffer = buffer->next;
		cmd->command = malloc(sizeof(char *) * (nb_arg + 1));
		while (lst)
		{
			if (ft_strcmp(lst->word, "|") == 0)
				break;
			else if (lst->is_op > 0)
				lst = lst->next;
			else
			{
				cmd->command[j] = ft_strdup(lst->word);
				j++;
			}
			lst = lst->next;
		}
		if (lst)
			lst = lst->next;
		cmd->command[j] = NULL;
		cmd++;
	}
	cmd->command = NULL;
	return (buffer_cmd);
}

int	get_number_of_pipe(t_token	*lst)
{
	int	nb;

	nb = 0;
	while (lst)
	{
		if (lst->is_op && ft_strncmp(lst->word, "|", 1) == 0)
			nb++;
		lst = lst->next;
	}
	return (nb);
}

char	**get_array_env(t_token *lst)
{
	int i;
	int	nb_line;
	char	**env;
	t_token	*buffer;

	i = 0;
	nb_line = 0;
	buffer = lst;
	while (buffer->next)
	{
		nb_line++;
		buffer = buffer->next;
	}
	env = malloc(sizeof(char *) * (nb_line + 1));
	while (lst->next)
	{
		env[i] = ft_strdup(lst->word);
		lst = lst->next;
		i++;
	}
	env[i] = "\0";
	return (env);
}