/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:58:57 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 15:58:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int		ispath_ok(char *path, char *name)
{
	DIR				*dir;
	struct dirent	*dent;

	if (name == (char *)1)
		return (0);
	if (!(dir = opendir(path)))
		return (0);
	while ((dent = readdir(dir)))
		if (!ft_strcmp(dent->d_name, name))
		{
			closedir(dir);
			return (1);
		}
	closedir(dir);
	return (0);
}

int		get_path_makestr(char **ret, char *path, char *name)
{
	int	path_len;

	path_len = ft_strlen(path);
	if (!(*ret = (char *)malloc2(path_len + 1 + ft_strlen(name) + 1)))
		return (-1);
	ft_strcpy(*ret, path);
	(*ret)[path_len] = '/';
	ft_strcpy(*ret + path_len + 1, name);
	return (0);
}

int		get_path_make_strarry(t_arg_main *arg_main, char ***path)
{
	t_arg	arg;
	int		tmp;

	if ((tmp = arg_get(arg_main, &arg, "PATH")))
		return (tmp);
	if (!(*path = split_command((char *)(arg.data), ':')))
	{
		arg_free(&arg);
		return (-1);
	}
	arg_free(&arg);
	return (0);
}

int		get_path(t_arg_main *arg_main, char **ret, char *name)
{
	char	**path;
	char	**tmp_path;
	int		tmp;

	if (ispath_ok("./", ft_strchr(name, '/') + 1))
	{
		*ret = ft_strdup(name);
		return (0);
	}
	if ((tmp = get_path_make_strarry(arg_main, &path)))
		return (tmp);
	tmp_path = path;
	while (*path)
	{
		if (ispath_ok(*path, name))
		{
			tmp = get_path_makestr(ret, *path, name);
			split_free_all(tmp_path);
			return (tmp);
		}
		path++;
	}
	split_free_all(tmp_path);
	return (1);
}
