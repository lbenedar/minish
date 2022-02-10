/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:18:54 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/15 23:15:06 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_ms_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		printf("%s=%s\n", data->envp[i]->var_name, data->envp[i]->var_value);
		i++;
	}
	return (0);
}
