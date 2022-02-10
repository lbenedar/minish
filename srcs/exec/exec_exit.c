/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:08:24 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:15:35 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(char **cmd, t_ms_data *data)
{
	int	i;

	printf("exit\n");
	i = 0;
	while (cmd[i])
		++i;
	if (i > 2)
	{
		out_error(data, "too many arguments", "exit");
		exit (1);
	}
	else if (i == 2)
		exit ((int)ft_atoi(cmd[1]));
	exit(0);
}
