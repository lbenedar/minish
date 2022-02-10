/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:44:14 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/17 23:59:32 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	output_sorted_envp(t_ms_data *data)
{
	t_env_content	**sorted_env;
	int				i;

	sorted_env = sort_env(data->envp);
	if (!sorted_env)
		return (1);
	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x %s=\"%s\"\n", sorted_env[i]->var_name,
			sorted_env[i]->var_value);
		++i;
	}
	ft_free_arr((void *)sorted_env);
	return (0);
}

static int	add_new_env(char **subarr, t_ms_data *data)
{
	int				i;
	t_env_content	**new_env;

	i = 0;
	while (data->envp[i])
		++i;
	new_env = malloc(sizeof(t_env_content *) * (i + 2));
	i = 0;
	while (data->envp[i])
	{
		new_env[i] = data->envp[i];
		++i;
	}
	new_env[i] = malloc(sizeof(t_env_content));
	new_env[i]->var_name = ft_strdup(subarr[0]);
	new_env[i]->var_value = ft_strdup(subarr[1]);
	new_env[i + 1] = 0;
	free(data->envp);
	data->envp = new_env;
	return (1);
}

void	search_env(char **subarr, t_ms_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strcmp(data->envp[i]->var_name, subarr[0]))
		{
			free(data->envp[i]->var_value);
			data->envp[i]->var_value = ft_strdup(subarr[1]);
			return ;
		}
		++i;
	}
	add_new_env(subarr, data);
}

int	exec_export(char **args, t_ms_data *data)
{
	int		j;
	char	**subarr;

	if (!args[1])
		return (output_sorted_envp(data));
	j = 1;
	while (args[j])
	{
		subarr = ft_split_one(args[j], '=');
		if (subarr[1])
		{
			search_env(subarr, data);
			free(subarr[1]);
		}
		free(subarr[0]);
		free(subarr);
		++j;
	}
	return (0);
}
