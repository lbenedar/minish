/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:35:46 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:58:10 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long long	*longdst;
	unsigned long long	*longsrc;
	unsigned char		*chrdst;
	unsigned char		*chrsrc;

	if ((!dst) && (!src))
		return (0);
	longdst = (unsigned long long *)dst;
	longsrc = (unsigned long long *)src;
	while (n >= 8)
	{
		*longdst++ = *longsrc++;
		n -= 8;
	}
	chrdst = (unsigned char *)longdst;
	chrsrc = (unsigned char *)longsrc;
	while (n--)
		*chrdst++ = *chrsrc++;
	return (dst);
}
