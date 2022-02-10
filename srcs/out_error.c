/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 16:37:49 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/16 20:59:29 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_error(void)
{
	if (errno)
	{
		if (errno > 0)
			exit(printf("%s\n", strerror(errno)) + errno);
		else
			exit(0);
	}
}

/*
**	Function, that output error by cmd (command that got error)
**	and error string that we got (custom or from strerror(errno))
*/

int	out_error(t_ms_data *data, char *error, char *cmd)
{
	ft_putstr(data->shell_name, 2);
	ft_putstr(": ", 2);
	ft_putstr(cmd, 2);
	ft_putstr(": ", 2);
	ft_putstr(error, 2);
	ft_putstr("\n", 2);
	errno = 0;
	return (-1);
}
