/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:18:11 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/20 14:25:50 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dir(t_cmd *cmd, char *path)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (!ft_strcmp(entry->d_name, cmd->main_cmd[0]))
		{
			closedir(dir);
			return (1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

static void	set_new_cmd(t_cmd *cmd, char *path)
{
	int		len;
	char	*str;
	char	*substr;

	substr = 0;
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] != '/')
		substr = ft_strjoin(path, "/");
	if (substr)
	{
		str = ft_strjoin(substr, cmd->main_cmd[0]);
		free(substr);
	}
	else
		str = ft_strjoin(path, cmd->main_cmd[0]);
	if (str)
	{
		free(cmd->main_cmd[0]);
		cmd->main_cmd[0] = str;
	}
	errno = 0;
}

static int	check_cmd(t_cmd *cmd, t_ms_data *data)
{
	struct stat	buf;
	int			res;
	char		*str;

	if (cmd->main_cmd[0][0] == '.')
	{
		str = ft_replace(cmd->main_cmd[0], ".", data->home_dir);
		free(cmd->main_cmd[0]);
		cmd->main_cmd[0] = str;
	}
	res = stat(cmd->main_cmd[0], &buf);
	if (!res && buf.st_size)
	{
		errno = 0;
		return (1);
	}
	return (0);
}

int	find_command(t_ms_data *data, t_cmd *cmd)
{
	int		i;
	char	**paths;

	i = -1;
	while (data->envp[++i])
		if (!ft_strcmp(data->envp[i]->var_name, "PATH"))
			break ;
	if (!data->envp[i])
		return (1);
	paths = ft_split(data->envp[i]->var_value, ':');
	i = -1;
	while (paths[++i])
	{
		if (check_dir(cmd, paths[i]))
		{
			set_new_cmd(cmd, paths[i]);
			ft_free_arr((void *)paths);
			return (0);
		}
	}
	ft_free_arr((void *)paths);
	if (check_cmd(cmd, data))
		return (0);
	errno = 127;
	return (1);
}
