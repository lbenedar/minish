/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_woq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:24:22 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/17 01:46:10 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_rmvdlr(char *str, t_tmp *tmp, char **ptr, t_ms_data *data)
{
	char	*env;
	int		n;

	ft_strjoin_pars(str, tmp, &(*ptr));
	n = 1;
	tmp->i++;
	while (((str[tmp->i] != ' ') && (str[tmp->i] != '\t')
			&& (str[tmp->i] != '$')) && (str[tmp->i] != '\0')
		&& (str[tmp->i] != '\'') && (str[tmp->i] != '\"'))
	{
		tmp->i++;
		n++;
	}
	env = ft_rmvdlr_utils(n, str, tmp);
	ft_get_env(tmp->prev_return, &env, data);
	ft_join_env(ptr, env);
	tmp->ndlr = tmp->ndlr + (n - strlen_p(env));
	tmp->i--;
	free(env);
}

static void	ft_q_rmv(char *str, t_tmp *tmp, char **ptr)
{
	while ((str[tmp->i] != '\'') && (str[tmp->i] != '\0'))
		tmp->i++;
	tmp->nq++;
	ft_strjoin_pars(str, tmp, &(*ptr));
}

static void	ft_qq_rmv(char *str, t_tmp *tmp, char **ptr, t_ms_data *data)
{
	tmp->nq++;
	while ((str[tmp->i] != '\"') && (str[tmp->i] != '\0'))
	{
		if (str[tmp->i] == '$')
		{
			ft_strjoin_pars(str, tmp, &(*ptr));
			ft_rmvdlr(str, tmp, &(*ptr), data);
		}
		tmp->i++;
	}
	ft_strjoin_pars(str, tmp, &(*ptr));
	tmp->j++;
	tmp->i++;
}

static void	ft_rmvquotes(char *str, t_tmp *tmp, char **ptr, t_ms_data *data)
{
	if (str[tmp->i] == '\'')
	{
		ft_strjoin_pars(str, tmp, &(*ptr));
		tmp->i++;
		tmp->j++;
		ft_q_rmv(str, tmp, &(*ptr));
		tmp->i++;
		tmp->j++;
	}
	else if (str[tmp->i] == '\"')
	{
		ft_strjoin_pars(str, tmp, &(*ptr));
		tmp->i++;
		tmp->j++;
		ft_qq_rmv(str, tmp, &(*ptr), data);
	}
}

char	*ft_str_woq(t_ms_data *data, char *str)
{
	char	*ptr;
	t_tmp	tmp;

	ptr = NULL;
	tmp.i = 0;
	tmp.j = 0;
	tmp.nq = 0;
	tmp.ndlr = 0;
	tmp.prev_return = data->prev_return;
	while (str[tmp.i] != '\0')
	{
		if ((str[tmp.i] == '\'') || (str[tmp.i] == '\"'))
		{
			ft_rmvquotes(str, &tmp, &ptr, data);
			tmp.nq++;
		}
		else if (str[tmp.i] == '$')
			ft_rmvdlr(str, &tmp, &ptr, data);
		if (str[tmp.i] != '\0')
			tmp.i++;
	}
	if (str[tmp.i] == '\0')
		ft_strjoin_pars(str, &tmp, &ptr);
	return (ptr);
}
