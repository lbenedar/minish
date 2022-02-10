/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:41:46 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/15 23:14:17 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_echo(char **cmd, t_usable_redir *redirs)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	if (redirs)
		NULL;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "-n") && (++i))
			n = 1;
		if (cmd[i])
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
			i++;
		}
	}
	if (n == 0)
		printf("\n");
	return (0);
}
