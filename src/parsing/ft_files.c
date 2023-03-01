#include "exec.h"
#include "minishell.h"
#include "parsing.h"

int	ft_read_file(t_token *lst, char *op)
{
	int	input;

	lst = lst->next;
	input = -1;
	if (access(lst->word, R_OK) != 0)
		perror(lst->word);
	else if (ft_strcmp(op, "<") == 0)
		input = open(lst->word, O_RDONLY);
	else if (ft_strcmp(op, "<<") == 0)
		input = ft_here_doc(lst->word);
	else
		input = -1;
	return (input);
}

int	ft_write_file(t_token *lst, char *op)
{
	int	output;

	lst = lst->next;
	output = -1;
	if (access(lst->word, F_OK) == 0 && access(lst->word, W_OK) == -1)
		perror(lst->word);
	else if (ft_strcmp (op, ">") == 0)
		output = open(lst->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (ft_strcmp(lst->word, ">>") == 0)
		output = open(lst->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (output);
}
