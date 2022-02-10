/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:20:43 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/18 12:45:21 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_output(t_ms_data *data, t_usable_redir *redirs,
	t_piped_io *desc)
{
	int	fd;

	fd = 1;
	if (redirs->output->type == redirect_a)
		fd = open(redirs->output->filename,
				O_APPEND | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	else if (redirs->output->type == redirect_o)
		fd = open(redirs->output->filename,
				O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (errno)
	{
		data->prev_return = errno;
		out_error(data, strerror(errno), redirs->output->filename);
		return (0);
	}
	close(desc->fd_out[1]);
	close(desc->fd_out[0]);
	desc->fd_out[0] = 0;
	desc->fd_out[1] = 0;
	redirs->fd_out = fd;
	return (1);
}

static int	read_input_file(t_ms_data *data, t_usable_redir *redirs,
	t_piped_io *desc)
{
	int		fd;

	fd = open(redirs->input->filename, O_RDONLY);
	if (errno)
	{
		data->prev_return = errno;
		out_error(data, strerror(errno), redirs->input->filename);
		return (0);
	}
	close(desc->fd_in[0]);
	desc->fd_in[0] = 0;
	redirs->fd_in = fd;
	return (1);
}

static int	setup_lastd(t_usable_redir *redirs)
{
	int		len;
	char	*str;
	char	result;

	len = ft_strlen(redirs->last_d->filename);
	str = readline("> ");
	while (str)
	{
		result = ft_memcmp(str, "\x18", 2);
		if (!result)
			break ;
		if (!ft_memcmp(str, redirs->last_d->filename, len + 1))
			break ;
		ft_putstr(str, redirs->fd_delim[1]);
		ft_putstr("\n", redirs->fd_delim[1]);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(redirs->fd_delim[1]);
	redirs->fd_delim[1] = 0;
	return (result);
}

int	setup_io(t_ms_data *data, t_usable_redir *redirs, t_piped_io *desc)
{
	if ((redirs->last_d) && (!setup_lastd(redirs)))
	{
		errno = 1;
		return (0);
	}
	if (errno && out_error(data, strerror(errno), redirs->filename_err))
		return (0);
	if (redirs->output && !open_output(data, redirs, desc))
		return (0);
	if (!redirs->input)
		return (1);
	if (redirs->last_d && redirs->input->type == redirs->last_d->type
		&& !ft_strcmp(redirs->input->filename, redirs->last_d->filename))
	{
		close(desc->fd_in[0]);
		desc->fd_in[0] = 0;
		redirs->fd_in = redirs->fd_delim[0];
		redirs->fd_delim[0] = 0;
	}
	else
		if (!read_input_file(data, redirs, desc))
			return (0);
	return (1);
}
