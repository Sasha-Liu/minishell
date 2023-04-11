/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsliu <hsliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:44:07 by sasha             #+#    #+#             */
/*   Updated: 2023/04/11 15:22:14 by hsliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/***  line_to_token_utils.c  ***/
int		ft_is_operator(char *buffer);
int		ft_is_redirection(char *word);
int		ft_is_pipe(char *word);
int		ft_is_word(char *buffer);
int		ft_set_quote_state(char c, int quote_state);

/***  ft_line_to_token.c  ***/
t_token	*ft_line_to_token(char *buffer);
int		ft_syntax_err(t_token *lst);
t_token	*ft_get_token(char **buffer);
t_token	*ft_is_token(char **buffer, int length);

/***  ft_set_pipe.c  ***/
void	ft_set_pipe(t_cmd *cmd, int n, int *p);
int		*ft_malloc_pipe(int n);
int		ft_count_pipe(t_token *lst);

/*	ft_get_cmd.c	*/
t_cmd	*ft_get_cmd(t_token *lst, int *size);
t_cmd	*ft_malloc_cmd(int n);
void	ft_free_cmd(t_cmd *cmd, int size);
void	ft_close_pipe_err(int *p, int i);

/***  parsing.c  ***/
int		ft_parsing(char *buffer, t_shell *shell);
void	ft_print_cmd(t_cmd *cmd, int size);

/***  dollar_exp_utils.c  ***/
char	*ft_strjoin_1(char *new_w, char **old, int n);
char	*ft_strjoin_2(char *new_w, char **old, t_token *env_lst);
int		ft_delimit_dollar(char *key);
char	*ft_add_equal(char *key);
char	*ft_get_para(char *search_key, t_token *env_lst);

/***  ft_dollar_exps  ***/
char	*ft_dollar_exps(char *word, t_token *env_lst);
int		ft_dollar_exps_lst(t_token *lst, t_token *env_lst);
void	ft_init_local_var(char *word, int *quote_st, int *i, char **new_w);

/***  ft_get_homedir  ***/
char	*ft_get_homedir(char *login);
char	*ft_find_line(char *login);
int		ft_delimit_login(char *login);

/***  tilde_exps_utils.c  ***/
char	*ft_tilde_exps(char *word, t_token *env_lst);
char	*ft_case_tilde_login(char *word);
char	*ft_case_tilde_slash(char *word, char *home);
char	*ft_case_tilde(char *word, char *home);
char	*ft_get_home(t_token *env_lst);

/***  ft_tilde_exps.c  ***/
int		ft_tilde_exps_lst(t_token *lst, t_token *env_lst);

/***  ft_exps_and_split.c  ***/
int		ft_exps_and_split(t_token **lst, t_token *env_lst);
int		ft_syntax_err_2(t_token *lst);
int		ft_exist_unquoted_space(char *word);

/***  ft_field_split.c  ***/
int		ft_split_lst(t_token **lst);
int		ft_split_word(t_token **node);

/***	ft_rm_quote.c	***/
void	ft_rm_quote_lst(t_token *lst);
void	ft_rm_quote_word(char *word);

/***	ft_redirect.c	***/
void	ft_redirect(t_token **lst, t_cmd *cmd, int size, t_shell *shell);
t_token	*ft_redirect_one(t_token *node, t_cmd *cmd, t_shell *shell);
void	ft_update_file(t_token *node, t_cmd *cmd);
void	ft_delete_redirect_lst(t_token **lst);
t_token	*ft_delete_redirect_node(t_token *node1);

/***	ft_init_command.c	***/
int		ft_init_command(t_token *lst, t_cmd *cmd, int size);
int		ft_init_one(t_token *node, t_cmd *cmd);
int		ft_count_args(t_token *node);
t_token	*ft_next_cmd(t_token *node);

/*	ft_here_doc.c	*/
int		ft_here_doc(char *limiter, t_shell *shell);
void	ft_child_here_doc(char *limiter, int *fd, t_shell *shell);

/*	ft_exist_status_exp.c	*/
char	*ft_exit_exps_node(char *word);
int		ft_exit_exps_lst(t_token *lst);
char	*ft_strjoin_3(char *new_word, char **old);

#endif