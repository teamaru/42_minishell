/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:58:55 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/19 17:12:34 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/includes/libft.h"


#define BUILTIN_NUM 7
#define TMPFILE "/tmp/my_tmp_file"
#define CMD_NUM 7
#define PRMPT "$ "
#define ROOT "/"
#define META_CHARS ";\'\"<>|$?\\."
#define DELIMITERS "|<> \t"
#define TOKEN_TYPE_NUM 5
#define MSG_HEADER "mini_shell "
#define MSG_EXIT "exit"
#define ERR_MSG_INVLD_CMD "command not found"
#define ERR_MSG_INVLD_OPT "invalid option"
#define ERR_MSG_INVLD_EXIT_CD "numeric argument required"
#define ERR_MSG_TOO_MANY_ARGS "too many arguments"
#define ERR_MSG_INVLD_SYNTX "syntax error near unexpected token"
#define ERR_MSG_QT_NOT_CLSD "quote is not closed"
#define ERR_MSG_AMBGS_RDRCT "ambiguous redirect"

typedef enum e_bool
{
  FALSE,
  TRUE,
} t_bool;

typedef enum e_result
{
  SUCCESS,
  FAILURE,
} t_result;

typedef enum e_exit_cd {
  SCCSS = 0,
  GNRL_ERR = 1,
  DENIED = 126,
  CMD_NOT_FND = 127,
  INVLD_EXT_ARG = 128,
  OUT_OF_EXT_STS = 255,
  INVLD_SYNTX = 258,
} t_exit_cd;

typedef enum e_f_dscrpt
{
  STDIN,
  STDOUT,
  STDERR,
} t_f_dscrpt;

typedef enum e_option
{
  NON,
  N = 'n',
  INVLD_OPT,
} t_option;

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
} t_meat_char;

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
} t_builtin_id;

typedef enum e_token_type
{
  TYPE_R_RDRCT,
  TYPE_RR_RDRCT,
  TYPE_L_RDRCT,
  TYPE_LL_RDRCT,
  TYPE_PIPE,
  TYPE_STR,
  TYPE_EXPDBL,
} t_token_type;

typedef struct s_argument
{
  char *arg;
  struct s_argument *next;
} t_argument;

typedef struct s_token
{
  struct s_token *prev;
  struct s_token *next;
  char *token;
  t_token_type type;
} t_token;

typedef struct s_cmd
{
  struct s_cmd *prev;
  struct s_cmd *next;
  t_token *args;
  t_token *rds;
} t_cmd;

typedef struct s_environ
{
  struct s_environ *next;
  struct s_environ *prev;
  char *key;
  char *value;
} t_environ;


typedef t_bool (*t_builtin_func)(const char **cmd_args, t_bool is_child_process);
typedef t_bool (*t_is_func)(char);
typedef void (*t_expand_func)(char**, t_token**);

typedef struct s_request
{
  t_token *tokens;
  t_cmd *cmds;
  t_environ *environs;
  t_builtin_func builtin_funcs[BUILTIN_NUM];

  char *cmd;
  t_builtin_id builtin_id;
  t_option option;
  t_argument *arguments;
  t_bool excution;
  t_exit_cd exit_cd;
} t_request;

typedef enum e_type_rd
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
} t_type_rd;

typedef struct s_heredocument
{
	char	*delimiter;
	t_bool	last_heredoc;
} t_demi_for_heredoc;

typedef struct s_redirection_list
{
	int							fd;
	t_type_rd					type;
	char						*file_path;
	t_demi_for_heredoc			*demi_heredoc;
	struct s_redirection_list	*next;
} t_redirection_list;

typedef struct s_heredoc_to_fd
{
	char	*contents;
	int		tmp_fd;
	char	*tmp_file_path;
} t_heredoc_to_fd;

typedef struct s_pipe_list
{
	t_redirection_list			*output_rd;
	t_redirection_list			*input_rd;
	t_heredoc_to_fd				*heredoc;
	const char					**cmd_args;
	struct s_pipe_list			*next;
	pid_t						pid;
} t_pipe_list;


char *get_chunk(char **line);
void parse_arguments(char **line);


/*
 *************
 ** request **
 *************
 */
/*
 ** request.c **
 */
 t_bool process_request(char *line);
 t_bool is_valid_request(void);
t_bool request_convert_to_pipe_list();
 void init_request(void);

/*
 *************
 ** builtin **
 *************
 */
/*
** command.c **
*/
void	init_cmds(char **cmds);
void free_cmds(char **cmds);
void parse_cmd(char **line);
void init_builtin_funcs();
t_builtin_id get_builtin_id(const char *token);
/*
** cd.c **
*/
t_bool execute_cd(const char **cmd_args, t_bool is_child_process);
/*
 ** echo.c **
 */
t_bool execute_echo(const char **cmd_args, t_bool is_child_process);
/*
 ** env.c **
 */
t_bool execute_env(const char **cmd_args, t_bool is_child_process);
/*
 ** exit.c **
 */
t_bool execute_exit(const char **cmd_args, t_bool is_child_process);
/*
 ** export.c **
 */
t_bool execute_export(const char **cmd_args, t_bool is_child_process);
/*
 ** pwd.c **
 */
t_bool execute_pwd(const char **cmd_args, t_bool is_child_process);
/*
 ** unset.c **
 */
t_bool execute_unset(const char **cmd_args, t_bool is_child_process);
/*
 *************
 ** convert **
 *************
 */
/*
** add_rd_node.c
*/
t_redirection_list	*add_new_rd_node(t_token_type token_type, t_redirection_list **input, t_redirection_list **output);
/*
** cmd_args.c
*/
const char	**create_cmd_args(t_token *args);
/*
** free_pipe_node.c
*/
void	free_pipe_node(t_pipe_list **node);
/*
** free_pipe_list.c
*/
void	free_pipe_list(t_pipe_list *list);
/*
** set_redirection_list.c
*/
t_result	set_redirection_lists(t_pipe_list **pipe_node, t_token *rds);
/*
** request_to_pipe_list.c
*/
t_pipe_list	*create_pipe_list(void);
/*
** set_heredoc.c
*/
void	set_heredocument(t_pipe_list **node, t_heredoc_to_fd **heredoc);

/*
 **************
 ** exection **
 **************
 */
/*
** create_environ.c **
*/
char	**env_list_to_array(t_environ *environs);
/*
** exec_pipe_list.c **
*/
void	child_exec_cmd(t_pipe_list *pipe_list);
void	execute_cmds(t_pipe_list *pipe_list);
/*
** handle_pipe.c **
*/
void	handle_pipelines(t_pipe_list *pipe_list);
/*
** serch_cmd_path.c **
*/
t_bool	search_path(char **cmd);
/*
** simple_builtin.c **
*/
t_result exec_simple_buitin(t_pipe_list *pipe_list, t_builtin_id builtin_id);
/*
** simple_cmd.c **
*/
void	exec_simple_cmd(t_pipe_list *pipe_list);

/*
 ************
 ** option **
 ************
 */
/*
** option.c **
*/
t_bool is_valid_option(char *option);
void parse_option(char **line);
/*
 **************
 ** argument **
 **************
 */
/*
 ** argument.c **
 */
 void parse_arguments(char **line);
 void free_arguments(t_argument **top);
/*
 ** list.c **
 */
t_argument	*new_argument(char *arg);
int listsize(t_argument *arguments);
char **list_to_array(t_argument *arguments);
void	append_argument(t_argument **top, t_argument *new);
/*
 ***********
 ** error **
 ***********
 */
/*
 ** error.c **
 */
t_bool print_err_msg(char *msg);
void my_exit(t_exit_cd exit_cd);
void	print_err_and_exit(char *msg, t_exit_cd exit_cd);
/*
 ***********
 ** utils **
 ***********
 */
/*
 ** utils1.c **
 */
t_bool is_white(int c);
void clear_char(char **line, int c);
void clear_white(char **line);
void multi_free(char **target);
void free_all(t_bool is_exit);
/*
** utils2.c **
*/
t_bool is_chunk(char c);
t_bool is_sgl_qt(char c);
t_bool is_quote(char c);
t_bool is_dbl_qt(char c);
t_bool is_end(char *line);
/*
** utils3.c **
*/
t_bool is_match_str(char *input, char *delimiter);
t_bool	is_dollar(char c);
t_bool	has_heredoc(t_heredoc_to_fd *heredoc);
t_bool	has_pipe(t_pipe_list *pipe_list);


/*
** free.c **
*/
void	free_set(void **dst, void *src);


/*
 ***********
 ** token **
 ***********
 */
/*
 ** token.c **
 */
void free_tokens(t_token **head);
t_token	*new_token(char *token);
void	append_token(t_token **head, t_token *new);
t_bool is_delimiter(int c);
t_bool find_closing_qt(char *line, int *i);
void get_token(t_token **head, char **line);
void tokenize(t_token **head, char *line);
int token_listsize(t_token *tokens);
void print_tokens(t_token *head);
char **token_list_to_array(t_token *token);

/*
 ***********
 ** parse **
 ***********
 */
/*
 ** parse.c **
 */
void free_cmd_list(t_cmd **head);
t_cmd	*new_cmd(void);
void	append_cmd(t_cmd **head, t_cmd *new);
void print_cmds(t_cmd *head);
void parse(void);
t_bool is_type_redirect(t_token *token);
t_bool is_type_heredoc(t_token *token);
t_bool is_valid_syntax(void);

/*
 ***************
 ** expansion **
 ***************
 */
/*
 ** expansion.c **
 */
t_bool is_env_end(char c);
char *get_env_value(char *key);
t_bool expand(void);
void free_environs(t_environ **head);
void make_environ_hash(void);
void replace_env_value(char *target_key, char *new_value);
t_environ *get_target_environ(const char *key);
t_environ	*new_environ(char *key, char *value);
void delete_environ(t_environ **head, t_environ *target_environ);
void print_environ(t_environ *head);
void	append_environ(t_environ **head, t_environ *new);

/*
 *************
 ** signal **
 *************
 */
/*
 ** signal.c **
 */
void init_signal(void);
void interrupt(int sig_id);



char *join_path(char *cdpath, char *path);
char *add_slash(char *cdpath);

/*
 ******************
 ** redirections **
 ******************
 */
/*
 ** change_reference.c **
 */
int	change_multi_references(t_pipe_list *cmd);
/*
 ******************
 ** heredocument **
 ******************
 */
/*
** close_and_unlink.c **
*/
void	close_and_unlink(t_heredoc_to_fd **heredoc, t_bool linkable);
/*
** form_heredocumet.c **
*/
void	form_heredocument(char *delimiter, char **heredoc);
/*
** delimiter_rm_quotes.c **
*/
char	*rm_quotes(char *str);
/*
** readline_heredoc.c **
*/
t_result	readline_input_heredoc(char **heredoc, char *delimiter);
/*
** expand_heredoc.c **
*/
t_result	expand_heredoc(char **contents);
/*
** write_tmp_file.c **
*/
t_result	write_heredoc(t_heredoc_to_fd *heredoc);
t_bool is_path_part(char *path);

/*
 ******************
 ** pipe **
 ******************
 */
/*
** operation.c **
*/
void	init_pipe_fd(int pipe_fd[2]);
t_bool	is_pipe_open(int pipe_fd[2]);
void	read_pipe(int pipe_fd[2]);
void	write_pipe(int pipe_fd[2]);
/*
** parent.c **
*/
void	parent_operate_pipe_fd(t_pipe_list *node, int last_pipe_fd[2], int new_pipe_fd[2]);
/*
** child.c **
*/
void	child_operate_pipe_fd(t_pipe_list *first, t_pipe_list *node, int last_pipe_fd[2], int new_pipe_fd[2]);

#endif
