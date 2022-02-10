/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:15:57 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:50:46 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strcpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while ((src[i]) && (i < len))
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = 0;
	return (i);
}

size_t	find_end_line(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && (s[i] != '\n'))
		i++;
	return (i);
}

char	*ft_strdup_line(const char *s)
{
	char	*newstr;
	size_t	i;

	if (!s)
		return (0);
	newstr = malloc(sizeof(char) * (find_end_line(s) + 1));
	if (!(newstr))
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		newstr[i] = s[i];
		++i;
	}
	newstr[i] = 0;
	return (newstr);
}

char	*strcat_newline(char **dst, const char *src)
{
	char	*subdst;
	size_t	len;

	if (!(*dst))
		return (*dst = ft_strdup_line(src));
	len = 0;
	while ((*dst)[len])
		len++;
	subdst = malloc(sizeof(char) * (len + find_end_line(src) + 1));
	if (!(subdst))
		return (0);
	ft_strcpy(subdst + ft_strcpy(subdst, *dst, len), src, find_end_line(src));
	free(*dst);
	*dst = subdst;
	return (subdst);
}

char	*skip_line(char *s)
{
	size_t	len;
	size_t	start;
	char	*subs;

	if (!s)
		return (0);
	start = find_end_line(s);
	len = 0;
	while (s[len])
		++len;
	if (start == len)
	{
		subs = malloc(sizeof(char));
		if (!(subs))
			return (0);
		subs[0] = 0;
		return (subs);
	}
	subs = malloc(sizeof(char) * (len - start));
	if (!(subs))
		return (0);
	ft_strcpy(subs, s + (start + 1), len - start + 1);
	return (subs);
}
