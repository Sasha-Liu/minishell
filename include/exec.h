#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include "builtin.h"

t_token	*ft_get_lst_cmd(t_token	*lst);
t_cmd	*ft_get_array_cmd(t_token *lst, int nb_cmd);
int		get_number_of_pipe(t_token	*lst);
char	**get_array_env(t_token *lst);
void	ft_exec(t_shell *shell);
int		ft_open_file(char *file, char *op);
int		ft_here_doc(char *limiter);
int		exec_builtin(t_shell *shell, char **cmd);
int	    ft_read_file(t_token *lst, char *op);
int	    ft_write_file(t_token *lst, char *op);
char	*ft_final_path(char **cmd, char **envp);
void	ft_free_split(char **array);
void	ft_open_close_dup(t_cmd *cmd, t_token *lst);
int	    first_cmds(t_cmd *cmd, char **env);
void	ft_close_fd(int **fd, t_shell *shell);
int		**ft_init_fd(int nb_pipe);
int 	loop(void);

#endif