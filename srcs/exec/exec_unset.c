/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:44:31 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/20 14:58:08 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_content	**copy_env(t_env_content **envp, int n)
{
	int				i;
	int				k;
	int				j;
	t_env_content	**new_envp;

	k = ft_size_arr((void *)envp);
	new_envp = malloc(sizeof(t_env_content *) * k);
	if (!new_envp)
		return (0);
	i = -1;
	j = 0;
	while (++i < k)
	{
		if (i != n)
		{
			new_envp[j] = malloc(sizeof(t_env_content));
			if (!new_envp[j])
				return (0);
			new_envp[j]->var_name = ft_strdup(envp[i]->var_name);
			new_envp[j]->var_value = ft_strdup(envp[i]->var_value);
			++j;
		}
	}
	new_envp[j] = 0;
	return (new_envp);
}

static void	remove_arg(t_ms_data *data, int n)
{
	int				i;
	t_env_content	**new_env;

	i = 0;
	while (data->envp[i])
		++i;
	new_env = copy_env(data->envp, n);
	if (!new_env)
		return ;
	free_env(data->envp);
	data->envp = new_env;
}

int	exec_unset(char **args, t_ms_data *data)
{
	int	i;
	int	j;

	j = 1;
	while (args[j])
	{
		i = 0;
		while (data->envp[i])
		{
			if (!ft_strcmp(data->envp[i]->var_name, args[j]))
			{
				remove_arg(data, i);
				break ;
			}
			++i;
		}
		++j;
	}
	return (0);
}
