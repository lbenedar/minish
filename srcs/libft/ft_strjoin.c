/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:24:46 by lbenedar          #+#    #+#             */
/*   Updated: 2021/03/26 20:24:49 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*newstr;

	if ((!s1) || (!s2))
		return (0);
	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	newstr = malloc((len1 + len2 + 1) * sizeof(char));
	if (!newstr)
		return (0);
	ft_memcpy(newstr, s1, len1);
	ft_memcpy(newstr + len1, s2, len2);
	newstr[len1 + len2] = 0;
	return (newstr);
}
