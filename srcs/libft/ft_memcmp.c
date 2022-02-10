/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 16:01:48 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:56:41 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*subs1;
	unsigned char	*subs2;

	i = 0;
	subs1 = (unsigned char *)s1;
	subs2 = (unsigned char *)s2;
	while (i < n)
	{
		if (subs1[i] - subs2[i])
			return (subs1[i] - subs2[i]);
		i++;
	}
	return (0);
}
