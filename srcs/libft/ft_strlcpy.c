/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:32:56 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:55:52 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if ((!dst) && (!src))
		return (0);
	i = 0;
	while (src[i])
	{
		if (size > i + 1)
			dst[i] = src[i];
		else
			break ;
		i++;
	}
	if (size != 0)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}
