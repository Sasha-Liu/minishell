#include "parsing.h"
#include "minishell.h"
#include "exec.h"
#include "builtin.h"

void	childs(t_shell *shell, char **cmd);

int	first_cmds(t_cmd *cmd, char **env)
{
	char	*path_cmd;
	int		pid;

	path_cmd = ft_final_path(cmd->command, env);
	pid = fork();
	if (pid == -1)
		perror(": fork failed\n");
	if (pid == 0)
	{
		close(cmd->read_fd);
		dup2(cmd->write_fd, STDOUT_FILENO);
		close(cmd->write_fd);
		execve(path_cmd, cmd->command, env);
	}
	close (cmd->write_fd);
	dup2(cmd->read_fd, STDIN_FILENO);
	close (cmd->read_fd);
	cmd++;
	return (0);
}

// void	childs(t_shell *shell, char **cmd)
// {
// 	if (shell->pid[shell->i] == 0)
// 	{
// 		// close(fd[shell->i][0]);
// 		// if (dup2(fd[shell->i][1], STDOUT_FILENO) == -1)
// 		// 	ft_printf("Error while duplicating et i = %d\n", shell->i);
// 		// close(fd[shell->i][1]);
// 		execve(shell->path_cmd, cmd, NULL);
// 		exit(0);
// 	}
// 	else
// 	{
// 		// close(fd[shell->i][1]);
// 		// if (dup2(fd[shell->i][0], STDIN_FILENO) == -1)
// 		// 	ft_printf("Error while duplicating\n");
// 		// close(fd[shell->i][0]);
// 		if (shell->path_cmd != NULL)
// 			free(shell->path_cmd);
// 	}
// }