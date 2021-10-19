/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 23:21:06 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/29 23:21:06 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

char *add_slash(char *cdpath)
{
  char *tmp;
  if (cdpath[ft_strlen(cdpath) - 1] == SLSH)
    return (cdpath);
  tmp = cdpath;
  cdpath = ft_strjoin(cdpath, "/");
  free(tmp);
  return (cdpath);
}

t_bool is_path_part(char *path)
{
  return (*path != PERIOD && *path != SLSH);
}

char *join_path(char *cdpath, char *path)
{
  char *tmp;

  tmp = cdpath;
  cdpath = ft_strjoin(cdpath, path);
  free(tmp);
  return (cdpath);
}

t_bool search_cdpath(char *path)
{
  t_environ *cdpath;
  char **cdpaths;
  int i;

  cdpath = get_target_environ("CDPATH");
  if (!cdpath)
    return (FALSE);
  cdpaths = ft_split(cdpath->value, ':');
  i = -1;
  while (cdpaths[++i])
  {
    cdpaths[i] = add_slash(cdpaths[i]);
    cdpaths[i] = join_path(cdpaths[i], path);
    if (chdir(cdpaths[i]) == -1)
      continue ;
    ft_putendl_fd(cdpaths[i], STDOUT);
    multi_free(cdpaths);
    return (TRUE);
  }
  multi_free(cdpaths);
  return (FALSE);
}

t_bool is_current_dir_exist(char *pwd)
{
  struct stat stat_buf;

  return(lstat(pwd, &stat_buf) == 0);
}

t_exit_cd execute_cd(const char **cmd_args, t_bool is_child_process)
{
  char pwd[BUFSIZ];
  char *path;
  t_bool is_changed;

  is_changed = FALSE;
  pwd[0] = '0';
  getcwd(pwd, BUFSIZ);
  replace_env_value("OLDPWD", pwd);
  path = (char *)cmd_args[1];
  if (!path)
    path = ROOT;
  if (*path == PERIOD)
    if (!is_current_dir_exist(pwd))
      print_err_msg(ERR_MSG_NO_FILE, SCCSS);
  if (is_path_part(path))
    is_changed = search_cdpath(path);
  if (!is_changed)
    if (chdir(path) == -1)
      print_err_msg(strerror(errno), GNRL_ERR);
  getcwd(pwd, BUFSIZ);
  replace_env_value("PWD", pwd);
  if (is_child_process)
    exit(SCCSS);
  return (SCCSS);
}
