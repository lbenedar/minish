/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:38:41 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/16 00:29:52 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_content	**copy_envp(t_env_content **envp)
{
	int				i;
	int				n;
	t_env_content	**new_envp;

	n = ft_size_arr((void *)envp);
	new_envp = malloc(sizeof(t_env_content *) * (n + 1));
	if (!new_envp)
		return (0);
	i = 0;
	while (i < n)
	{
		new_envp[i] = malloc(sizeof(t_env_content));
		if (!new_envp[i])
			return (0);
		new_envp[i]->var_name = envp[i]->var_name;
		new_envp[i]->var_value = envp[i]->var_value;
		++i;
	}
	new_envp[i] = 0;
	return (new_envp);
}

static void	ft_qsort_arr(t_env_content **envp)
{
	int		i;
	int		j;
	char	*curr_name;
	char	*curr_value;

	i = 0;
	while (envp[i])
	{
		curr_name = envp[i]->var_name;
		curr_value = envp[i]->var_value;
		j = i;
		while (j > 0 && ft_strcmp(curr_name, envp[j - 1]->var_name) < 0)
		{
			envp[j]->var_name = envp[j - 1]->var_name;
			envp[j]->var_value = envp[j - 1]->var_value;
			--j;
		}
		envp[j]->var_name = curr_name;
		envp[j]->var_value = curr_value;
		++i;
	}
}

t_env_content	**sort_env(t_env_content **envp)
{
	t_env_content	**envp_sorted;

	envp_sorted = copy_envp(envp);
	if (!envp_sorted)
		return (0);
	ft_qsort_arr(envp_sorted);
	return (envp_sorted);
}		

void	set_env(t_ms_data *data, char **envp)
{
	int		i;
	int		n;
	char	**subarr;

	data->envp = NULL;
	n = ft_size_arr((void *)envp);
	data->envp = malloc(sizeof(t_env_content *) * (n + 1));
	if (errno)
		check_error();
	i = 0;
	while (i < n)
	{
		subarr = ft_split_one(envp[i], '=');
		data->envp[i] = malloc(sizeof(t_env_content));
		if (errno)
			check_error();
		data->envp[i]->var_name = subarr[0];
		data->envp[i]->var_value = subarr[1];
		free(subarr);
		++i;
	}
	data->envp[i] = 0;
}
