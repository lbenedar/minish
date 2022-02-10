/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:45:44 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:57:37 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long long	*longb;
	unsigned char		*chrb;

	longb = (unsigned long long *)s;
	while (n >= 8)
	{
		*longb++ = 0;
		n -= 8;
	}
	chrb = (unsigned char *)longb;
	while (n--)
		*chrb++ = 0;
}
