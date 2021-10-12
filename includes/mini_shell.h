/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:58:55 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/12 09:34:52 by jnakahod         ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/includes/libft.h"

#define CMD_NUM 7
#define PRMPT "$ "
#define ROOT "/"
#define META_CHARS ";\'\"<>|$?\\."
#define DELIMITERS "|<> \t"
#define TOKEN_TYPE_NUM 5
#define MSG_HEADER "mini_shell: "
#define MSG_EXIT "exit\n"
#define ERR_MSG_INVLD_CMD "command not found\n"
#define ERR_MSG_INVLD_OPT "invalid option\n"
#define ERR_MSG_INVLD_EXIT_CD "numeric argument required\n"
#define ERR_MSG_TOO_MANY_ARGS "too many arguments\n"
#define ERR_MSG_INVLD_SYNTX "syntax error near unexpected token \n"
#define ERR_MSG_QT_NOT_CLSD "quote is not closed\n"
#define ERR_MSG_AMBGS_RDRCT "ambiguous redirect\n"

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
} t_meat_char;

typedef enum e_cmd_id
{
  ECHO,
  CD,
  PWD,
  EXPORT,
  UNSET,
  ENV,
  EXIT,
  INVLD_CMD,
} t_cmd_id;

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

typedef struct s_request
{
  t_token *tokens;
  t_cmd *cmds;
  t_environ *environs;

  char *cmd;
  t_cmd_id cmd_id;
  t_option option;
  t_argument *arguments;
  t_bool excution;
  int exit_cd;
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

typedef t_bool (*t_cmd_func)(void);
typedef t_bool (*t_is_func)(char);
typedef void (*t_expand_func)(char**, t_token**);

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
 ** command **
 *************
 */
/*
** command.c **
*/
void	init_cmds(char **cmds);
void free_cmds(char **cmds);
void parse_cmd(char **line);
void init_cmd_funcs(t_cmd_func *cmd_funcs);
t_cmd_id get_cmd_id(char **cmds, char *cmd);
/*
** cd.c **
*/
t_bool execute_cd(void);
/*
 ** echo.c **
 */
t_bool execute_echo(void);
/*
 ** env.c **
 */
t_bool execute_env(void);
/*
 ** exit.c **
 */
t_bool execute_exit(void);
/*
 ** export.c **
 */
t_bool execute_export(void);
/*
 ** pwd.c **
 */
t_bool execute_pwd(void);
/*
 *************
 ** convert **
 *************
 */
/*
** cmd_args.c
*/
const char	**create_cmd_args(t_token *args);
/*
** free_pipe_list.c
*/
void	free_pipe_list(t_pipe_list *list);
/*
** redirection_list.c
*/
t_result	set_redirection_lists(t_pipe_list **pipe_node, t_token *rds);
/*
** request_to_pipe_list.c
*/
t_pipe_list	*create_pipe_list(void);
/*
** set_heredoc.c
*/
void	set_heredocument(t_pipe_list **node);

/*
 **************
 ** exection **
 **************
 */
/*
** execution.c **
*/
t_bool is_execution(char **line);
t_bool execute_executable(void);
/*
** execution.c **
*/
void	execute_cmds(t_pipe_list *pipe_list);
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
void my_exit(int exit_cd);
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
void free_all(void);
/*
** utils2.c **
*/
t_bool is_chunk(char c);
t_bool is_sgl_qt(char c);
t_bool is_quote(char c);
t_bool is_dbl_qt(char c);
t_bool is_end(char *line);

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
 ************
 ** expand **
 ************
 */
/*
 ** expand.c **
 */
t_bool expand(void);
void free_environs(t_environ **head);
void make_environ_hash(void);

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

/*
 ******************
 ** redirections **
 ******************
 */
/*
 ** change_reference.c
 */
int	change_multi_references(t_pipe_list *cmd);

#endif
