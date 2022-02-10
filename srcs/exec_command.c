/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:46:06 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/18 14:02:55 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	choose_command(t_ms_data *data, t_cmd *cmd, t_usable_redir *redirs,
t_piped_io *desc)
{
	if (!ft_strcmp(cmd->main_cmd[0], "cd"))
		exec_cd(cmd, data, redirs);
	else if (!ft_strcmp(cmd->main_cmd[0], "pwd"))
		exec_pwd(data);
	else if (!ft_strcmp(cmd->main_cmd[0], "exit"))
		exec_exit(cmd->main_cmd, data);
	else if (!ft_strcmp(cmd->main_cmd[0], "echo"))
		exec_echo(cmd->main_cmd, redirs);
	else if (!ft_strcmp(cmd->main_cmd[0], "env"))
		exec_env(data);
	else if (!ft_strcmp(cmd->main_cmd[0], "export"))
		exec_export(cmd->main_cmd, data);
	else if (!ft_strcmp(cmd->main_cmd[0], "unset"))
		exec_unset(cmd->main_cmd, data);
	else if (!find_command(data, cmd))
	{
		exec_file(cmd->main_cmd, data, desc, redirs);
		return ;
	}
	else
		out_error(data, "command not found", cmd->main_cmd[0]);
	data->prev_return = errno;
	if (errno && errno != 127)
		out_error(data, strerror(errno), cmd->main_cmd[0]);
}

void	exec_command(t_ms_data *data, t_cmd *cmd, t_usable_redir *redirs,
t_piped_io *desc)
{
	desc->o_dup = dup(1);
	dup2(redirs->fd_out, 1);
	close(redirs->fd_out);
	if (cmd->main_cmd[0])
		choose_command(data, cmd, redirs, desc);
	close(redirs->fd_in);
	dup2(desc->o_dup, 1);
	close(desc->o_dup);
}
