/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:42:14 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/16 00:02:08 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstr;
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	newstr = malloc(sizeof(char) * (len + 1));
	if (!(newstr))
		return (0);
	ft_strcpy(newstr, s);
	return (newstr);
}
