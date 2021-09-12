/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:58:55 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/25 21:58:55 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/includes/libft.h"

#define CMD_NUM 7
#define PRMPT "$ "
#define ROOT "/"
#define META_CHARS ";\'\"<>|$?\\."
#define MSG_HEADER "mini_shell: "
#define MSG_EXIT "exit\n"
#define ERR_MSG_INVLD_CMD "command not found\n"
#define ERR_MSG_INVLD_OPT "invalid option\n"
#define ERR_MSG_INVLD_EXIT_CD "numeric argument required\n"
#define ERR_MSG_TOO_MANY_ARGS "too many arguments\n"

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
  SLASH = '/',
  PERIOD = '.',
  SEMICOLON = ';',
  SGL_QT = '\'',
  DBL_QT = '\"',
  OPTION = '-',
  BCK_SLSH = '\\',
  GRTR = '>',
  LESS = '<'
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

typedef struct s_argument
{
  char *arg;
  struct s_argument *next;
} t_argument;

typedef struct s_request
{
  char *cmd;
  t_cmd_id cmd_id;
  t_option option;
  t_argument *arguments;
  t_bool excution;
  int exit_cd;
} t_request;

typedef t_bool (*t_cmd_func)(t_request*);
typedef t_bool (*t_is_func)(char);


char *get_chunk(char **line);
void parse_arguments(t_request *request, char **line);


/*
 *************
 ** request **
 *************
 */
/*
 ** request.c **
 */
 t_bool process_request(t_request *request, char *line);
 void parse_request(t_request *request, char **line);
 t_bool is_valid_request(t_request *request);
 t_bool exec_request(t_request *request);
 void init_request(t_request *request);

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
void parse_cmd(t_request *request, char **line);
void init_cmd_funcs(t_cmd_func *cmd_funcs);
t_cmd_id get_cmd_id(char **cmds, char *cmd);
/*
** cd.c **
*/
t_bool execute_cd(t_request *request);
/*
 ** echo.c **
 */
t_bool execute_echo(t_request *request);
/*
 ** env.c **
 */
t_bool execute_env(t_request *request);
/*
 ** exit.c **
 */
t_bool execute_exit(t_request *request);
/*
 ** export.c **
 */
t_bool execute_export(t_request *request);
/*
 ** pwd.c **
 */
t_bool execute_pwd(t_request *request);
/*
 **************
 ** exection **
 **************
 */
/*
** execution.c **
*/
t_bool is_execution(t_request *request, char **line);
t_bool execute_executable(t_request *request);
/*
 ************
 ** option **
 ************
 */
/*
** option.c **
*/
t_bool is_valid_option(char *option);
void parse_option(t_request *request, char **line);
/*
 **************
 ** argument **
 **************
 */
/*
 ** argument.c **
 */
 void parse_arguments(t_request *request, char **line);
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
t_bool print_err_msg(t_request *request, char *msg);
void my_exit(t_request *request, int exit_cd);
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
void free_all(t_request *request);
/*
** utils2.c **
*/
t_bool is_chunk(char c);
t_bool is_sgl_qt(char c);
t_bool is_qt(char c);
t_bool is_dbl_qt(char c);
t_bool is_end(char *line);

#endif
