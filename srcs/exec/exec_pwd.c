/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:01:45 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:21:56 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_ms_data *data)
{
	char	*str;

	str = ft_replace(data->curr_dir, "~", data->home_dir);
	printf("%s\n", str);
	free(str);
	return (0);
}
