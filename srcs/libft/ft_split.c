/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:39:43 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/18 14:17:20 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fillarr_split(char **fillarray, int num,
						char const *start, size_t end)
{
	fillarray[num] = ft_strndup(start, end);
	if (!fillarray[num])
		return (0);
	return (1);
}

static int	ft_fillsplit(char const *s, char c, char **fillarray)
{
	size_t	i;
	int		num;
	int		first;

	i = 0;
	num = 0;
	first = 0;
	while (s[i])
	{
		if ((s[i] == c) && (first != -1))
		{
			fillarray[num] = ft_strndup(s + first, i - first);
			if (!fillarray[num])
				return (0);
			first = -1;
			num++;
		}
		else if ((s[i] != c) && (first == -1))
			first = i;
		i++;
	}
	if ((i > 0) && (s[i - 1] != c))
		return (ft_fillarr_split(fillarray, num, s + first, i - first));
	return (1);
}

static size_t	ft_splitnum(char const *s, char c)
{
	size_t	i;
	size_t	num;

	if (!(*s))
		return (0);
	i = 0;
	num = 0;
	if (s[i])
		num++;
	while (s[i])
	{
		if (s[i] == c)
			if ((s[i + 1] != c) && (s[i + 1] != 0))
				num++;
		i++;
	}
	return (num);
}

char	**ft_clean_split(char **array)
{
	int		i;

	if (!array)
		return (0);
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	num;
	char	**array;

	if (!s)
		return (0);
	while ((*s) && (*s == c))
		s++;
	num = ft_splitnum(s, c);
	array = ft_calloc(sizeof(char *), (num + 1));
	if (!array)
		return (0);
	array[num] = 0;
	if (num)
		if (!ft_fillsplit(s, c, array))
			return (ft_clean_split(array));
	return (array);
}
