/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:24:38 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/17 23:32:45 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_tmp_cmd(int n, t_arr *tmp_cmd)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (tmp_cmd[i].comand != NULL)
			free(tmp_cmd[i].comand);
		if (tmp_cmd[i].red != NULL)
			free(tmp_cmd[i].red);
		i++;
	}
	if (tmp_cmd != NULL)
		free(tmp_cmd);
}

static void	ft_split_cmd_redir(t_ms_data *data, char **arr, t_arr *tmp_cmd)
{
	int	n;

	n = 0;
	while (n < data->nbr_cmds)
	{
		tmp_cmd[n].comand = ft_fill_tmp_cmd(arr[n]);
		tmp_cmd[n].red = ft_fill_tmp_redir(arr[n]);
		n++;
	}
}

void	ft_get_data(t_ms_data *data, t_arr *tmp_cmd)
{
	int	n;

	n = 0;
	while (n < data->nbr_cmds)
	{
		data->cmds[n] = (t_cmd *)malloc(sizeof(t_cmd) * 1);
		data->cmds[n]->nbr_cmd_args = ft_nbr_cmd_args(tmp_cmd[n].comand);
		data->cmds[n]->main_cmd = (char **)malloc(sizeof(char *)
				* (data->cmds[n]->nbr_cmd_args + 1));
		ft_fill_cmd_data(data, tmp_cmd, n);
		data->cmds[n]->nbr_redir = ft_nbr_redir(tmp_cmd[n].red);
		data->cmds[n]->redirect = (t_refile **)malloc(sizeof(t_refile *)
				* ((data->cmds[n]->nbr_redir) + 1));
		ft_fill_redir_data(data, tmp_cmd, n);
		n++;
	}
	data->cmds[n] = NULL;
}

int	parser(char *str, t_ms_data *data)
{
	char	**arr;
	t_arr	*tmp_cmd;

	if (ft_check_str(str))
		return (1);
	data->nbr_cmds = ft_nbr_pipes_in_str(str);
	arr = (char **)malloc(sizeof(char *) * (data->nbr_cmds + 1));
	arr[data->nbr_cmds] = 0;
	tmp_cmd = (t_arr *)malloc(sizeof(t_arr) * data->nbr_cmds);
	data->cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (data->nbr_cmds + 1));
	if ((arr == NULL) || (tmp_cmd == NULL) || (data->cmds == NULL))
		return (1);
	ft_split_cmds(&arr, str);
	ft_split_cmd_redir(data, arr, tmp_cmd);
	ft_free_arr((void *)arr);
	ft_get_data(data, tmp_cmd);
	ft_free_tmp_cmd(data->nbr_cmds, tmp_cmd);
	return (0);
}
