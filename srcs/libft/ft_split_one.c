/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:32:28 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:52:23 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_one(char *str, char c)
{
	int		i;
	char	**arr;

	arr = malloc(sizeof(char *) * 3);
	i = 0;
	while (str[i] && str[i] != c)
		++i;
	arr[0] = ft_strndup(str, i);
	if (*(str + i) == c)
		arr[1] = ft_strdup(str + (i + 1));
	else
		arr[1] = 0;
	arr[2] = 0;
	return (arr);
}
