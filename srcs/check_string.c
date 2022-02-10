/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:18:46 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/17 17:58:36 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cycle_redirect_o(t_refile *cmd, t_usable_redir *redirs)
{
	int	fd;

	if (redirs->output && (!errno))
	{
		fd = open(redirs->output->filename,
				O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (errno)
		{
			redirs->filename_err = cmd->filename;
			return ;
		}
		close(fd);
		redirs->output = cmd;
	}
	else if (!redirs->output)
		redirs->output = cmd;
}

static void	cycle_redirect(t_refile *cmd, t_usable_redir *redirs)
{
	int	fd;

	if (cmd->type == redirect_d)
	{
		redirs->input = cmd;
		redirs->last_d = cmd;
	}
	else if ((cmd->type == redirect_i) && (!errno))
	{
		fd = open(cmd->filename, O_RDONLY);
		if (errno)
		{
			redirs->filename_err = cmd->filename;
			return ;
		}
		close(fd);
		redirs->input = cmd;
	}
	else
		cycle_redirect_o(cmd, redirs);
}

static void	setup_redirs(t_usable_redir *redirs, t_piped_io	*desc)
{
	if (pipe(redirs->fd_delim))
	{
		errno = 1;
		return ;
	}
	redirs->input = NULL;
	redirs->output = NULL;
	redirs->last_d = NULL;
	redirs->filename_err = NULL;
	redirs->fd_in = desc->fd_in[0];
	redirs->fd_out = desc->fd_out[1];
}

static void	check_redirect(t_ms_data *data, t_cmd *cmd, t_piped_io *desc)
{
	int				i;
	t_usable_redir	redirs;

	setup_redirs(&redirs, desc);
	if (errno)
		return ;
	i = 0;
	while (cmd->redirect[i])
	{
		cycle_redirect(cmd->redirect[i++], &redirs);
		if (errno)
		{
			data->prev_return = errno;
			out_error(data, strerror(errno), redirs.filename_err);
			close(redirs.fd_out);
			free_redirs(&redirs);
		}
	}
	if (!setup_io(data, &redirs, desc))
		close(redirs.fd_out);
	else
		exec_command(data, cmd, &redirs, desc);
	free_redirs(&redirs);
}

void	check_seq(t_ms_data *data)
{
	int			i;
	t_piped_io	desc;

	if (pipe(desc.fd_e))
		out_error(data, "couldn't create pipe", "-");
	desc.e_dup = dup(2);
	dup2(desc.fd_e[1], 2);
	close(desc.fd_e[1]);
	i = 0;
	while (data->cmds[i])
	{
		setup_fd(&desc, data, i);
		check_redirect(data, data->cmds[i], &desc);
		++i;
	}
	dup2(desc.e_dup, 2);
	close(desc.e_dup);
	out_fd(&desc);
}
