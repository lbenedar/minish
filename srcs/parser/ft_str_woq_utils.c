/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_woq_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:21:32 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/18 12:58:41 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_change_env(char *p, char **env)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = strlen_p(p);
	str = (char *)malloc(sizeof(char) * (n + 1));
	while (p[i] != '\0')
	{
		str[i] = p[i];
		i++;
	}
	str[i] = '\0';
	free(*env);
	*env = str;
}

static void	ft_change_empty_env(char **env)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 1);
	str[0] = '\0';
	free(*env);
	*env = str;
}

static void	ft_change_ret_value(int prev_return, char **env)
{
	int		i;
	char	*str;
	char	*p;

	i = 0;
	p = ft_itoa_pars(prev_return);
	while (p[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (p[i] != '\0')
	{
		str[i] = p[i];
		i++;
	}
	str[i] = '\0';
	free(*env);
	free(p);
	*env = str;
}

void	ft_get_env(int prev_return, char **env, t_ms_data *data)
{
	int	res;
	int	i;

	i = 0;
	if (((strlen_p("$")) == (strlen_p(*env))) && ((*env)[0] == '$'))
		return ;
	if (((strlen_p("$?")) == (strlen_p(*env)))
		&& ((*env)[0] == '$') && ((*env)[1] == '?'))
	{
		ft_change_ret_value(prev_return, env);
		return ;
	}
	while (data->envp[i] != NULL)
	{
		res = strcmp_p(data->envp[i]->var_name, *env + 1);
		if (res == 0)
			break ;
		i++;
	}
	if (data->envp[i] == NULL)
		ft_change_empty_env(env);
	else
		ft_change_env(data->envp[i]->var_value, env);
}

void	ft_join_env(char **ptr, char *env)
{
	char	*p;
	int		i;
	int		res;

	p = NULL;
	i = 0;
	res = strlen_p(*ptr) + strlen_p(env);
	p = (char *)malloc(sizeof(char) * (res + 1));
	while (i < strlen_p(*ptr))
	{
		p[i] = (*ptr)[i];
		i++;
	}
	res = 0;
	while (env[res] != '\0')
	{
		p[i] = env[res];
		i++;
		res++;
	}
	p[i] = '\0';
	free(*ptr);
	*ptr = p;
}
