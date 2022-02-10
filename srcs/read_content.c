/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:08:09 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/16 15:11:27 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_end_quotes(char *line, int start)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == '\"')
			if (line[i - 1] != '\\')
				return (start + (i - 1));
		++i;
	}
	return (start - 1);
}

static int	set_data(char **str, char *line)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	end = -1;
	start = 0;
	while (line[i] && line[i] == ' ')
		++i;
	while (line[i] && line[i] != '\"')
		++i;
	start = i + 1;
	if (i > 0 && line[i - 1] != '\\' && line[i] == '\"' && start)
		end = find_end_quotes(line + i, start);
	if (end - start >= 0)
		*str = ft_strndup(line + start, end - start);
	else
		return (1);
	return (0);
}

static int	parse_l_conf(t_ms_data *data, char *line)
{
	if (!line[0])
		return (0);
	if (line[0] == 'S')
	{
		free(data->shell_name);
		return (set_data(&(data->shell_name), line + 1));
	}
	else if (line[0] == 'P' && line[1] == 'S' && line[2] == '1'
		&& !data->ps1_sample)
		return (set_data(&(data->ps1_sample), line + 3));
	else if (line[0] == 'P' && line[1] == 'S' && line[2] == '2'
		&& !data->ps2_sample)
		return (set_data(&(data->ps2_sample), line + 3));
	return (1);
}

static void	parse_content(t_ms_data *data, char *line)
{
	if (parse_l_conf(data, line))
	{
		ft_putstr("Error/n Configuration file have problems", 2);
		exit(1);
	}
	free(line);
}

/*
**	This function is parsing config file "minishell.conf" and
**	fill t_ms_data with data of prompt
*/

void	read_content(t_ms_data *data)
{
	int		fd;
	int		gnl_res;
	char	*line;

	fd = open("config/minishell.conf", O_RDONLY);
	if (fd < 0)
		return ;
	gnl_res = get_next_line(fd, &line);
	while (gnl_res)
	{
		if (gnl_res == -1)
		{
			errno = 1;
			check_error();
		}
		parse_content(data, line);
		gnl_res = get_next_line(fd, &line);
	}
	close(fd);
	if (!gnl_res)
		parse_content(data, line);
	else
		return ;
}
