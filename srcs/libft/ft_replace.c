/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:59:20 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/16 00:00:47 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Function that replace "sample" string with "value" string
**	in "main" string
*/

char	*ft_replace(const char *main, const char *sample, const char *value)
{
	char	*pos;

	pos = ft_strnstr(main, sample, ft_strlen(main));
	if (!pos)
		return (ft_strdup(main));
	return (ft_strljoin(value, pos + ft_strlen(sample), ft_strlen(pos)));
}
