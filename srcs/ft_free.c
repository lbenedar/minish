/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:55:44 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/17 19:41:55 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_arr(void **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_env(t_env_content **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		if (env[i]->var_name)
			free(env[i]->var_name);
		if (env[i]->var_value)
			free(env[i]->var_value);
		free(env[i]);
		++i;
	}
	free(env);
}

void	free_redirs(t_usable_redir *redir)
{
	if (redir->fd_delim[1])
		close(redir->fd_delim[1]);
	if (redir->fd_delim[0])
		close(redir->fd_delim[0]);
}

static void	free_cmd(t_cmd *cmd)
{
	int	j;

	j = 0;
	if (cmd->redirect)
	{
		while (cmd->redirect[j])
		{
			free(cmd->redirect[j]->filename);
			free(cmd->redirect[j]);
			++j;
		}
		free(cmd->redirect);
	}
	j = 0;
	if (cmd->main_cmd)
	{
		while (cmd->main_cmd[j])
			free(cmd->main_cmd[j++]);
		free(cmd->main_cmd);
	}
}

void	free_cmds(t_ms_data *data)
{
	int	i;

	i = 0;
	if (!data->cmds)
		return ;
	while (data->cmds[i])
	{
		free_cmd(data->cmds[i]);
		free(data->cmds[i]);
		++i;
	}
	free(data->cmds);
	data->cmds = NULL;
}
