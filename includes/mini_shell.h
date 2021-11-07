/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:58:55 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/07 23:26:11 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"

# define BUILTIN_NUM 7
# define TMPFILE "/tmp/my_tmp_file"
# define CMD_NUM 7
# define PRMPT "$ "
# define ROOT "/"
# define META_CHARS ";\'\"<>|$?\\."
# define DELIMITERS "|<> \t"
# define TOKEN_TYPE_NUM 5
# define MSG_HEADER "mini_shell "
# define MSG_EXIT "exit"
# define ERR_MSG_INVLD_CMD "command not found"
# define ERR_MSG_INVLD_OPT "invalid option"
# define ERR_MSG_INVLD_EXIT_CD "numeric argument required"
# define ERR_MSG_TOO_MANY_ARGS "too many arguments"
# define ERR_MSG_INVLD_SYNTX "syntax error near unexpected token"
# define ERR_MSG_QT_NOT_CLSD "quote is not closed"
# define ERR_MSG_AMBGS_RDRCT "ambiguous redirect"
# define ERR_MSG_NO_FILE "No such file or directory"
# define ERR_MSG_HOME_NOT_SET "HOME not set"
# define ERR_MSG_NOT_VLD_IDNTFR "not a valid identifier"
# define ERR_MSG_PERM_DENIED "Permission denied"
# define ERR_MSG_NOT_DIR "Not a directory"
# define ERR_MSG_IS_DIR "is a directory"

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_result
{
	SUCCESS,
	FAILURE,
}	t_result;

typedef enum e_exit_cd
{
	SCCSS = 0,
	GNRL_ERR = 1,
	DENIED = 126,
	CMD_NOT_FND = 127,
	INVLD_EXT_ARG = 128,
	OUT_OF_EXT_STS = 255,
	INVLD_SYNTX = 258,
}	t_exit_cd;

typedef enum e_f_dscrpt
{
	STDIN,
	STDOUT,
	STDERR,
}	t_f_dscrpt;

typedef enum e_option
{
	NON,
	N = 'n',
	INVLD_OPT,
}	t_option;

typedef enum e_meta_char
{
	SLSH = '/',
	B_SLSH = '\\',
	PERIOD = '.',
	SGL_QT = '\'',
	DBL_QT = '\"',
	HYPHEN = '-',
	R_RDRCT = '>',
	L_RDRCT = '<',
	DLL = '$',
	SPC = ' ',
	QSTN = '?',
}	t_meat_char;

typedef enum e_builtin_id
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NON_BUILTIN,
}	t_builtin_id;

typedef enum e_token_type
{
	TYPE_R_RDRCT,
	TYPE_RR_RDRCT,
	TYPE_L_RDRCT,
	TYPE_LL_RDRCT,
	TYPE_PIPE,
	TYPE_STR,
	TYPE_EXPDBL,
}	t_token_type;

typedef struct s_argument
{
	char				*arg;
	struct s_argument	*next;
}	t_argument;

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	char			*token;
	t_token_type	type;
}	t_token;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	t_token			*args;
	t_token			*rds;
}	t_cmd;

typedef struct s_environ
{
	struct s_environ	*next;
	struct s_environ	*prev;
	char				*key;
	char				*value;
	t_bool				is_declear;
}	t_environ;

typedef struct s_pwd
{
	struct s_pwd	*next;
	struct s_pwd	*prev;
	char			*dir;
}	t_pwd;

typedef t_exit_cd	(*t_builtin_func)(
		const char **cmd_args, t_bool is_child_process);
typedef t_bool		(*t_is_func)(char);
typedef void		(*t_expand_func)(char**, t_token**);

typedef struct s_request
{
	t_token			*tokens;
	t_cmd			*cmds;
	t_environ		*environs;
	t_builtin_func	builtin_funcs[BUILTIN_NUM];
	t_builtin_id	builtin_id;
	t_bool			excution;
	t_exit_cd		exit_cd;
	pid_t			pid;
	t_bool			interrupt_heredocument;
	char			*oldpwd;
	t_pwd			*pwd;
}	t_request;

typedef enum e_type_rd
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}	t_type_rd;

typedef struct s_heredocument
{
	char	*delimiter;
	t_bool	last_heredoc;
}	t_demi_for_heredoc;

typedef struct s_redirection_list
{
	int							fd;
	t_type_rd					type;
	char						*file_path;
	t_demi_for_heredoc			*demi_heredoc;
	struct s_redirection_list	*next;
}	t_redirection_list;

typedef struct s_heredoc_to_fd
{
	char	*contents;
	int		tmp_fd;
	char	*tmp_file_path;
}	t_heredoc_to_fd;

typedef struct s_pipe_list
{
	t_redirection_list			*output_rd;
	t_redirection_list			*input_rd;
	t_heredoc_to_fd				*heredoc;
	const char					**cmd_args;
	struct s_pipe_list			*next;
	pid_t						pid;
}	t_pipe_list;

/*
 *************
 ** request **
 *************
 */
/*
 ** request.c **
 */
t_bool				process_request(char *line);
t_bool				request_convert_to_pipe_list(void);
void				init_request(void);

/*
 *************
 ** builtin **
 *************
 */
/*
** builtin.c **
*/
void				init_cmds(char **cmds);
void				free_cmds(char **cmds);
void				init_builtin_funcs(void);
t_builtin_id		get_builtin_id(const char *token);
/*
** cd.c **
*/
void				renew_pwd(char *path);
char				*stringify_pwd(void);
t_bool				is_current_dir_exist(void);
t_bool				search_cdpath(char *path);
t_exit_cd			execute_cd(const char **cmd_args, t_bool is_child_process);
/*
 ** echo.c **
 */
t_exit_cd			execute_echo(const char **cmd_args,
						t_bool is_child_process);
/*
 ** env.c **
 */
t_exit_cd			execute_env(const char **cmd_args, t_bool is_child_process);
/*
 ** exit.c **
 */
int					str_arr_size(const char **strs);
t_bool				is_all_digits(const char *s);
t_exit_cd			execute_exit(const char **cmd_args,
						t_bool is_child_process);
/*
 ** export.c **
 */
void				add_declear_pwd(char **split,
						t_bool *is_declear, char *key);
t_bool				replace_duplicated_environ(char *key,
						char *value, t_bool is_declear);
char				**split_key_value(char *arg, t_bool *is_declear);
t_exit_cd			declare_env(t_bool is_child_process);
t_exit_cd			execute_export(const char **cmd_args,
						t_bool is_child_process);
/*
 ** pwd1.c **
 */
void				print_pwd(void);
void				init_pwd(void);
t_exit_cd			execute_pwd(const char **cmd_args, t_bool is_child_process);
/*
 ** pwd2.c **
 */
void				replace_oldpwd(void);
void				normalize_pwd(void);
void				replace_pwd(char **split, t_bool flg);
char				*stringify_pwd(void);
void				renew_pwd(char *path);
/*
 ** unset.c **
 */
t_exit_cd			execute_unset(const char **cmd_args,
						t_bool is_child_process);
/*
 ** utils.c **
 */
t_bool				is_key_exist(char *key);
t_bool				is_valid_identifier(const char *arg);
t_exit_cd			return_or_exit(t_exit_cd exit_cd, t_bool is_child_process);
char				*add_slash(char *cdpath);
char				*join_path(char *cdpath, char *path);
/*
 ** list.c **
 */
void				move_pwd_head(t_pwd **head, t_pwd *pwd);
void				delete_pwd(t_pwd **head, t_pwd *target_pwd);
void				free_pwd(t_pwd **head);
t_pwd				*new_pwd(char *dir);
void				append_pwd(t_pwd **head, t_pwd *new);
/*
 *************
 ** convert **
 *************
 */
/*
** add_rd_node.c
*/
t_redirection_list	*add_new_rd_node(
						t_token_type token_type,
						t_redirection_list **input,
						t_redirection_list **output);
/*
** cmd_args.c
*/
const char			**create_cmd_args(t_token *args);
/*
** free_pipe_node.c
*/
void				free_pipe_node(t_pipe_list **node);
/*
** free_pipe_list.c
*/
void				free_pipe_list(t_pipe_list *list);
/*
** set_redirection_list.c
*/
t_result			set_redirection_lists(t_pipe_list **pipe_node,
						t_token *rds);
/*
** request_to_pipe_list.c
*/
t_pipe_list			*create_pipe_list(void);
/*
** set_heredoc.c
*/
t_result			set_heredocument(
						t_pipe_list **node, t_heredoc_to_fd **heredoc);

/*
 *************
 ** environ **
 *************
 */
/*
** environ.c **
*/
t_bool				set_environ(char **split, t_bool flg, t_bool is_declear);
void				replace_env_value(char *target_key, char *new_value);
t_environ			*get_target_environ(const char *key);
void				print_environ(t_environ *head);
void				make_environ_hash(void);
/*
** list.c **
*/
void				move_environ_head(t_environ **head, t_environ *environ);
void				delete_environ(t_environ **head, t_environ *target_environ);
void				free_environs(t_environ **head);
t_environ			*new_environ(char *key, char *value, t_bool is_declear);
void				append_environ(t_environ **head, t_environ *new);
/*
** shlvl.c **
*/
void				update_shlvl(void);
/*
** utils.c **
*/
t_bool				is_env_end(char c);
char				*get_env_key(char *token);
char				*get_env_value(char *key);
int					get_env_len(char *token);

/*
 **************
 ** exection **
 **************
 */
/*
** check_executable_cmd_path.c **
*/
t_exit_cd			check_executable_cmd_path(const char *cmd_path,
						char **err_msg);
/*
** create_environ.c **
*/
t_bool				is_execution(char **line);
char				**env_list_to_array(t_environ *environs);
/*
** exec_pipe_list.c **
*/
void				child_exec_cmd(t_pipe_list *pipe_list);
void				execute_cmds(t_pipe_list *pipe_list);
/*
** exec_pipe_list.c **
*/
char				*get_dir_path(const char *cmd_path);
/*
** handle_pipe.c **
*/
pid_t				handle_pipelines(t_pipe_list *pipe_list);
/*
** serch_cmd_path.c **
*/
t_exit_cd			search_path(char **cmd);
/*
** simple_builtin.c **
*/
t_result			exec_simple_buitin(t_pipe_list *pipe_list,
						t_builtin_id builtin_id);
/*
** simple_cmd.c **
*/
void				cmd_set_exit_cd(int status, pid_t changed_pid);

/*
** split_path.c **
*/
void				exec_simple_cmd(t_pipe_list *pipe_list);
char				**split_path(char *path, char delimiter);
/*
** wait_process.c **
*/
void				wait_processes(t_pipe_list *pipe_list, pid_t last_child_pid);

/*
 ***********
 ** error **
 ***********
 */
/*
 ** error.c **
 */
t_bool				print_err_msg(char *msg, t_exit_cd exit_cd);
void				my_exit(t_exit_cd exit_cd);
t_exit_cd			builtin_err(char *msg, t_exit_cd exit_cd,
						t_bool is_child_process);
void				print_err_and_exit(char *msg, t_exit_cd exit_cd);
void				print_err_and_exit_free(char **msg, t_exit_cd exit_cd);
/*
 ***********
 ** utils **
 ***********
 */
/*
 ** utils1.c **
 */
t_bool				is_white(int c);
void				clear_char(char **line, int c);
void				clear_white(char **line);
void				multi_free(char **target);
void				free_all(t_bool is_exit);
/*
** utils2.c **
*/
t_bool				is_chunk(char c);
t_bool				is_sgl_qt(char c);
t_bool				is_quote(char c);
t_bool				is_dbl_qt(char c);
t_bool				is_end(char *line);
/*
** utils3.c **
*/
t_bool				is_match_str(char *input, char *delimiter);
t_bool				is_dollar(char c);
t_bool				has_heredoc(t_heredoc_to_fd *heredoc);
t_bool				has_pipe(t_pipe_list *pipe_list);
t_bool				is_enable_environ_path(void);
/*
** utils4.c **
*/
void				nothing(int sig_no);

/*
** free.c **
*/
void				free_set(void **dst, void *src);

/*
 ***********
 ** token **
 ***********
 */
/*
** token.c **
*/
void				get_delimiter(t_token **head, char **line);
void				get_token(t_token **head, char **line);
t_bool				split_token(t_token **head, t_token **token);
void				insert_token(
						t_token **head,
						t_token *new_token, t_token *target_token);
void				tokenize(t_token **head, char *line);
/*
** list1.c **
*/
void				move_token_head(t_token **head, t_token *token);
void				delete_token(t_token **head, t_token *target_token);
void				free_tokens(t_token **head);
t_token				*new_token(char *token);
void				append_token(t_token **head, t_token *new);
/*
** list2.c **
*/
void				insert_tokens(t_token **head,
						t_token *new_tokens, t_token *target_token);
void				replace_token(t_token *token, char *new_token);
int					token_listsize(t_token *tokens);
char				**token_list_to_array(t_token *tokens);
/*
** utils1.c **
*/
t_bool				is_redirect(char c);
t_bool				is_doble_redirect(char *line);
t_bool				is_eos_token(t_token *token);
t_bool				is_delimiter(int c);
void				print_tokens(t_token *head);
/*
** utils2.c **
*/
t_token_type		get_token_type(char *token);
void				prepare_token_types(char **token_types);
void				dispose_token_types(char **token_types);
t_bool				find_closing_qt(char *line, int *i);
void				test_token(void);
/*
***********
** parse **
***********
*/
/*
** parse.c **
*/
void				print_cmds(t_cmd *head);
t_bool				is_valid_syntax(void);
void				parse(void);
/*
 ** list.c **
 */
void				free_cmd_list(t_cmd **head);
t_cmd				*new_cmd(void);
void				append_cmd(t_cmd **head, t_cmd *new);
/*
 ** utils.c **
 */
t_bool				is_type_heredoc(t_token *token);
t_bool				is_type_redirect(t_token *token);
t_bool				is_type_meta(t_token *token);
t_bool				is_quote_closed(t_token *token);
t_bool				is_valid_token_pair(t_token *token);

/*
 ***************
 ** expansion **
 ***************
 */
/*
 ** expansion.c **
 */
t_bool				expand_tokens(t_token **head);
void				expand_quote(char **token, t_token **expanded_tokens);
void				expand_env(char **token, t_token **expanded_tokens);
char				*expand_token(t_expand_func expand_func, char *token);
t_bool				expand(void);
/*
 ** utils1.c **
 */
char				*join_expanded_tokens(t_token *expanded_tokens);
int					get_str_len(char *token);
void				get_word(t_token **new_tokens, char **line);
void				split_word(t_token **new_tokens, char *token);
t_bool				is_file_path(t_token *token);
/*
 ** utils2.c **
 */

int					keylen(char *s);
void				move_token_pointer(char **token, int i);
void				append_doll(char **token, t_token **expanded_tokens, int i);
/*
 *************
 ** signal **
 *************
 */
/*
 ** interrupt.c **
 */
void				init_signal_in_execution(void);
void				init_int_act_in_execution(void);
void				int_act_in_execution(void);
void				interrupt_in_execution(int	sig_id);

/*
 ** quit.c **
 */
void				quit_act_in_execution(void);
void				quit_act_in_execution(void);
void				quit_in_pipe_execution(int sig_id);
void				quit_act_in_pipe_execution(void);

void	int_act_in_execution(void);
/*
 ** signal.c **
 */
void				init_signal(void);
void				interrupt(int sig_id);
void				quit(int sig_id);

/*
 ******************
 ** redirections **
 ******************
 */
/*
 ** change_reference.c **
 */
int					change_multi_references(t_pipe_list *cmd, char **err_msg);
/*
 ** change_reference.c **
 */
t_bool				is_last_heredoc(t_redirection_list *node);
t_bool				is_heredoc(t_redirection_list *node);

/*
 ******************
 ** heredocument **
 ******************
 */
/*
** close_and_unlink.c **
*/
void				close_and_unlink(
						t_heredoc_to_fd **heredoc, t_bool linkable);
/*
** form_heredocumet.c **
*/
void				form_heredocument(char *delimiter, char **heredoc);
/*
** delimiter_rm_quotes.c **
*/
char				*rm_quotes(char *str);
/*
** readline_heredoc.c **
*/
t_result			readline_input_heredoc(char **heredoc, char *delimiter);
/*
** expand_heredoc.c **
*/
t_result			expand_heredoc(char **contents);
/*
** signal_in_heredoc.c **
*/
t_result			set_signal_in_heredocument(void);
/*
** write_tmp_file.c **
*/
t_result			write_heredoc(t_heredoc_to_fd *heredoc);
t_bool				is_path_part(char *path);

/*
 ******************
 ** pipe **
 ******************
 */
/*
** operation.c **
*/
void				init_pipe_fd(int pipe_fd[2]);
t_bool				is_pipe_open(int pipe_fd[2]);
void				read_pipe(int pipe_fd[2]);
void				write_pipe(int pipe_fd[2]);
/*
** parent.c **
*/
void				parent_operate_pipe_fd(
						t_pipe_list *node,
						int last_pipe_fd[2],
						int new_pipe_fd[2]);
/*
** child.c **
*/
void				child_operate_pipe_fd(
						t_pipe_list *first, t_pipe_list *node,
						int last_pipe_fd[2], int new_pipe_fd[2]);

#endif
