/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:01:10 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:53:05 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	subi;
	size_t	j;

	i = 0;
	if (!(*needle))
		return ((char *)haystack);
	while ((haystack[i] != 0) && (i < len))
	{
		j = 0;
		subi = i;
		while ((needle[j]) && (i + j < len))
		{
			if (needle[j] != haystack[subi])
				break ;
			subi++;
			j++;
		}
		if (!needle[j])
			break ;
		i++;
	}
	if ((haystack[i]) && (i < len))
		return ((char *)&haystack[i]);
	return (0);
}
