/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:30:31 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:57:05 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*subs;

	i = 0;
	subs = (char *)s;
	while (s[i])
	{
		if ((subs[i]) == c)
			return (subs + i);
		i++;
	}
	if (subs[i] == c)
		return (subs + i);
	return (0);
}
