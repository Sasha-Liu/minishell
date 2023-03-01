#include "parsing.h"
#include "minishell.h"
#include "exec.h"
#include "builtin.h"

void	no_pipe(t_shell *shell);

void	ft_exec(t_shell *shell)
{
	int		*fd;
	t_cmd	*cmd;
	
	fd = ft_malloc_pipe(shell->nb_pipe);
	cmd = shell->cmd;
	ft_set_pipe(cmd, shell->nb_pipe, fd);
	ft_open_close_dup(cmd, shell->parsed_input);
	while (shell->parsed_input)
	{
		if (ft_strcmp(shell->parsed_input->word, "|") != 0)
			first_cmds(cmd, shell->env);
		if (shell->i < shell->nb_pipe)	
			shell->parsed_input = shell->parsed_input->next;
		shell->parsed_input = shell->parsed_input->next;
	}
	ft_printf("%s\n", cmd->command[0]);
}

// void	no_pipe(t_shell *shell)
// {
	
// }
