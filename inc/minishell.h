/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:36:00 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/30 21:53:07 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define PROMPT "mini $ "
# define PATH_MAX 4096
# define ANSI_COLOR_GREEN "\033[0;32m"
# define ANSI_COLOR_BLUE "\033[0;34m"
# define ANSI_COLOR_RESET "\033[0m"
# define RD_END 0
# define WR_END 1
# define INTERACTIVE 0
# define NON_INTERACTIVE 1
# define HEREDOC 2
# define HEREDOC_ERROR "mini: warning: here-document at line "

extern int	g_signal;

typedef enum e_type
{
	PIPE,
	GTHAN,
	STHAN,
	H_DOC,
	APPEND,
	WORD,
}	t_type;

typedef struct s_tokens
{
	char			*value;
	t_type			token;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}	t_tokens;

typedef struct s_redirect
{
	int		here_doc;
	int		fd;
	char	*filename;
}	t_redir;

typedef struct s_command
{
	char				**cmd_array;
	char				*full_path;
	int					error_fd;
	t_redir				*redir_in;
	t_redir				*redir_out;
	struct s_command	*prev;
	struct s_command	*next;
}	t_cmd;

typedef struct s_env
{
	int				exported;
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_utils
{
	t_env	*envs;
	int		custom_envs;
	int		status;
	int		exit_status;
	int		cmds_amount;
	char	*builtins[8];
	char	*homedir;
}	t_utils;

typedef struct s_expand
{
	char			*old_value;
	char			*new_value;
	struct s_expand	*next;
}	t_exp;

/*          MAIN FUNCTIONS         */

void		ft_shloop(t_utils *utils);
void		init_utils(t_utils *utils, char **envs);
t_tokens	*ft_lexer(char *line);
t_cmd		*ft_parser(t_tokens *lexer_nodes, t_utils *utils);
void		ft_expander(t_cmd *nodes, t_utils *utils, int exit_status);
void		ft_executor(t_cmd *parser_nodes, t_utils *utils);
char		**ft_create_envs(t_utils *utils);

/*          LEXER FUNCTIONS         */

int			ft_check_syntax(t_tokens *lexer_nodes, char **line);

/*          STRUCT FUNCTIONS         */

int			ft_addlast(t_tokens **lexer, t_tokens *node);
void		ft_addlast_pnode(t_cmd **list, t_cmd *node);
void		ft_create_parser_nodes(t_tokens **lex_nodes, t_cmd *cmd_node,
				t_utils *utils);

/*          SIGNAL FUNCTIONS         */

void		handle_signal(int signal);
void		handle_signal_interactive(int signal);
void		*handle_error_ctrl_d(char *stop, int cmds_amount);
void		set_signals(int mode);
void		detect_ctrl_c(t_utils *utils);

/*          REDIR FUNCTIONS         */

t_redir		*hdoc_redir(t_tokens **lexer_nodes, t_cmd *parser_nodes,
				t_utils *utils);
t_redir		*append_gthan_redir(char *file_name, int token, t_utils *utils,
				t_cmd *parser_nodes);
t_redir		*sthan_redir(char *file_name, t_utils *utils, t_cmd *parser_nodes);
void		*exit_redir(int error, t_redir *redir_node, t_utils *utils);
int			open_fd(char *file_name, int mode);
int			ft_fork_hdoc(t_tokens **lexer_nodes, t_cmd *parser_nodes,
				t_redir *redir_node, t_utils *utils);

/*          BUILTINS FUNCTIONS         */

int			ft_pwd(t_env *env_list);
int			ft_cd(t_utils *utils, t_cmd *cmd);
int			ch_path(t_env *env_list, char *arg, char *str);
int			ft_env(t_env *env_list, int fd);
int			ft_echo(char **args, int fd);
int			ft_export(t_env **env_list, char **cmd_array, int fd);
int			ft_unset(t_env **env_list, char **array_keys);
int			ft_exit(char **args, int fd, t_utils *utils);
void		exec_builtins(t_cmd *parser_nodes, t_utils *utils, int fd);

/*          ENV FUNCTIONS         */

t_env		*ft_init_envs(char **envs);
t_env		*ft_create_env_node(char *env);
t_env		*ft_get_env_from_list(t_env *env_list, char *key);
int			ft_update_env_value(t_env *node, char *value);
t_env		*ft_clear_env_node(t_env *node);
void		ft_add_env_to_list(t_env **env_list, t_env *new_node);
int			ft_clear_env_list(t_env *env_list);
char		*ft_get_identifier(char *str);
char		*ft_get_env_value(char *key_value);

/*          EXPORT FUNCTIONS         */

int			ft_print_env(t_env *env_list, int fd);
void		*ft_print_stderr(char *str);
int			create_and_add_env_to_list(t_env **env_list, char *key_and_value);
void		*free_and_null(char **str);

/*          EXPAND FUNCTIONS         */

t_exp		*ft_free_one_expand_node(t_exp *expand_values);
void		*ft_free_all_expand_nodes(t_exp *expand_values);
t_exp		*ft_append_exp_node(t_exp *expand_nodes, t_exp *new_node);
t_exp		*ft_scan_expansions(char *str, t_env *env_list,	int exit_stat);
t_exp		*ft_build_exp_node(char *env, t_env *env_node);
char		ft_update_quote_state(char c, char status);
void		ft_norm_and_add(t_exp **expand_nodes, t_exp *node, char quote);
char		*ft_expand(char *str, t_exp **expand, int tot_len);
int			ft_get_new_str_len(char *str, t_exp *expand_values);
char		**ft_word_splitting(char **array, int pos);
void		ft_exp_hd(t_redir *redir_node, t_utils *utils);
char		*ft_expand_tilde_aux(char *str, t_utils *utils);

/*          EXECUTOR FUNCTIONS         */

void		ft_search_path(t_cmd *parser_nodes, t_utils *utils);
int			ft_is_builtin(t_cmd *parser_nodes, t_utils *utils);
void		ft_exec_builtin(t_cmd *parser_nodes, t_utils *utils, int pipe);
char		**ft_node_to_char(t_env *envs);
void		ft_dup_fds(t_cmd *parser_nodes, int prev_read, int *pipe_fd);
void		ft_close_fds(t_cmd *parser_nodes, int prev_read, int *pipe_fd);
int			is_directory(t_cmd *parser_nodes);

/*          AUX FUNCTIONS         */

int			ft_isspace(char c);
int			ft_is_metacharacter(int c);
char		*ft_get_value(char **line);
int			ft_read_to_file(char *stop, int cmds_amount, char *f_name);
int			ft_count_cmds_args(t_tokens *nodes, int len);
char		*ft_random_filename(void);
int			ft_remove_parser_quotes(t_cmd *parser_nodes);
char		*ft_remove_quotes(char *str);
int			get_pid(void);
void		get_short_path(char *short_pathname, char *cwd, t_utils *utils);
void		get_user_and_hostname(char *info_machine, t_env *envs);
char		*get_username(void);
char		*find_username(char **lines, char *uid_str, int option);
char		*read_file_username(char *path_file);
char		*read_file_for_uid(int fd, char *uid, char *tmp);
void		free_split(char **split);
void		ft_wait_for_childs(int i, int *exit_status);
void		get_homedir(t_utils *utils);
void		ft_call_child(char *path_file);
char		*ft_search_passwd(char *line, char *uid_str);
char		*ft_search_mount(char *line);
void		write_error_fd(char *target, char *error, int fd);

/*          FREE FUNCTIONS         */

void		free_loop(t_tokens *lexer_nodes, t_cmd *parser_nodes);
int			ft_free_lexer(t_tokens **lexer);
void		*ft_free_one_parser(t_cmd *parser);
void		ft_free_parser(t_cmd *parser_nodes);
void		*ft_free_redir(t_redir *redir_node);

#endif
