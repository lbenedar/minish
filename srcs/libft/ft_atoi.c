/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 22:15:15 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/16 00:03:14 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	int	num;
	int	neg;

	num = 0;
	neg = 1;
	while ((*nptr == ' ') || (*nptr == '\t') || (*nptr == '\n')
		|| (*nptr == '\r') || (*nptr == '\f') || (*nptr == '\v'))
		nptr++;
	if ((*nptr == '-') || (*nptr == '+'))
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while ((*nptr >= '0') && (*nptr <= '9'))
	{
		num = num * 10 + (*nptr - '0') * neg;
		nptr++;
	}
	return (num);
}
