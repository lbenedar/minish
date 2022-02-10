/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:14:52 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/18 14:08:58 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	create_line(char **str, char **linestr)
{
	char	*substr;

	if (!(strcat_newline(linestr, *str)))
	{
		free(*str);
		*str = 0;
		if (*linestr)
			free(*linestr);
		linestr = 0;
		return (0);
	}
	substr = skip_line(*str);
	if (!substr)
	{
		free(*str);
		*str = 0;
		if (*linestr)
			free(*linestr);
		linestr = 0;
		return (0);
	}
	free(*str);
	(*str) = substr;
	return (1);
}

static ssize_t	find_create_line(char **str, char **substr,
								char **line, ssize_t line_end)
{
	ssize_t	len;

	len = find_end_line(*str);
	if (!create_line(str, substr))
		return (-1);
	if (((*str)[0]) || ((!(*str)[0]) && (len == line_end - 1)))
	{
		*line = *substr;
		return (1);
	}
	free(*str);
	*str = 0;
	return (0);
}

static ssize_t	read_line(char **str, char **substr, int fd, char **line)
{
	ssize_t		r_res;
	ssize_t		result;

	(*str) = malloc(BUFFER_SIZE + 1);
	r_res = read(fd, *str, BUFFER_SIZE);
	while (r_res)
	{
		if (r_res == -1)
		{
			free(*str);
			*str = 0;
			return (-1);
		}
		(*str)[r_res] = 0;
		result = find_create_line(str, substr, line, r_res);
		if (result)
			return (result);
		(*str) = malloc(BUFFER_SIZE + 1);
		r_res = read(fd, *str, BUFFER_SIZE);
	}
	if (*str)
		free(*str);
	*str = 0;
	return (0);
}

static ssize_t	read_file(char **str, char **substr, int fd, char **line)
{
	ssize_t		result;

	if (*str)
	{
		*line = *substr;
		if (*line)
			return (1);
	}
	*line = 0;
	result = read_line(str, substr, fd, line);
	if (result)
		return (result);
	if (!(*substr))
	{
		*substr = malloc(sizeof(char));
		if (!(*substr))
			return (-1);
		**substr = 0;
	}
	*line = *substr;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*str;
	char		*substr;
	size_t		len_line;
	size_t		len;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (line == NULL))
		return (-1);
	substr = 0;
	if (!str)
		return (read_file(&str, &substr, fd, line));
	len_line = find_end_line(str);
	len = (u_int)ft_strlen(str);
	if (!create_line(&str, &substr))
		return (-1);
	if ((!(*str)) && (len_line + 1 != len))
	{
		free(str);
		str = 0;
	}
	return (read_file(&str, &substr, fd, line));
}
