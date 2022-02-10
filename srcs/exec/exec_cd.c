/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 16:03:59 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:12:55 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choose_path(char *path, t_ms_data *data)
{
	char	*temp;
	int		res_ch;

	if (path[0] == '~')
	{
		temp = ft_replace(path, "~", data->home_dir);
		res_ch = chdir(temp);
		free(temp);
	}
	else if (path[0] == '$' && (path[1] >= 'A' && path[1] <= 'Z'))
		res_ch = chdir(getenv(path + 1));
	else if (path[0] == '$' && path[1] == '?')
	{
		errno = ENOTDIR;
		res_ch = -1;
	}
	else
		res_ch = chdir(path);
	return (res_ch);
}

int	change_dir(char *path, t_ms_data *data)
{
	int		res_ch;
	char	*new_dir;

	res_ch = choose_path(path, data);
	if (!res_ch)
	{
		free(data->old_dir);
		data->old_dir = ft_strdup(data->curr_dir);
		free(data->curr_dir);
		new_dir = getcwd(malloc(sizeof(char) * (PATH_MAX + 1)), PATH_MAX + 1);
		if (errno)
			exit(1);
		data->curr_dir = ft_replace(new_dir, data->home_dir, "~");
		free(new_dir);
	}
	return (res_ch);
}

static	void	cd_out_wo_tilda(char *str, char *str_sample)
{
	if (!str)
		return ;
	if (str[0] == '~')
		printf("%s%s\n", str_sample, str + 1);
	else
		printf("%s\n", str);
}

int	exec_cd(t_cmd *cmd, t_ms_data *data, t_usable_redir *redirs)
{
	int	result;

	if (errno && redirs)
		return (1);
	if (cmd->main_cmd[1] && cmd->main_cmd[2])
		return (out_error(data, "too many arguments", "cd"));
	else if (!cmd->main_cmd[1] || !ft_memcmp(cmd->main_cmd[1], "~", 2))
		return (change_dir(data->home_dir, data));
	else if (!ft_memcmp(cmd->main_cmd[1], "-", 2))
	{
		result = change_dir(data->old_dir, data);
		cd_out_wo_tilda(data->curr_dir, data->home_dir);
		return (result);
	}
	else
		return (change_dir(cmd->main_cmd[1], data));
}
