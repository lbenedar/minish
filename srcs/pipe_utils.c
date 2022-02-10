/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:29:39 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/17 16:36:57 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_fd(int fd, int fd_out)
{
	char	*line;
	int		result;

	result = get_next_line(fd, &line);
	while (result)
	{
		if (result < 0)
			return ;
		ft_putstr(line, fd_out);
		ft_putstr("\n", fd_out);
		free(line);
		result = get_next_line(fd, &line);
	}
	ft_putstr(line, fd_out);
	free(line);
}

int	setup_fd(t_piped_io *desc, t_ms_data *data, int i)
{
	if (pipe(desc->fd_in))
		return (out_error(data, "couldn't create pipe", "-"));
	if (i > 0 && desc->fd_out[0])
	{
		read_fd(desc->fd_out[0], desc->fd_in[1]);
		close(desc->fd_out[0]);
	}
	close(desc->fd_in[1]);
	if (pipe(desc->fd_out))
		return (out_error(data, "couldn't create pipe", "-"));
	return (0);
}

void	out_fd(t_piped_io *desc)
{
	if (desc->fd_out[0])
	{
		read_fd(desc->fd_out[0], 1);
		close(desc->fd_out[0]);
	}
	read_fd(desc->fd_e[0], 2);
	close(desc->fd_e[0]);
}
