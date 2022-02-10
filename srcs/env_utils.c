/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:01:43 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/16 00:11:30 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

char	**env_to_str(t_env_content **content)
{
	int		i;
	char	**arr;
	char	*substr;

	i = ft_size_arr((void *)content);
	arr = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (content[i])
	{
		substr = ft_strjoin(content[i]->var_name, "=");
		if (errno)
			check_error();
		arr[i] = substr;
		substr = ft_strjoin(arr[i], content[i]->var_value);
		if (errno)
			check_error();
		free(arr[i]);
		arr[i] = substr;
		++i;
	}
	arr[i] = 0;
	return (arr);
}
