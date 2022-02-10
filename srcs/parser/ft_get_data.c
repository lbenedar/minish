/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:23:44 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/18 12:57:49 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_nbr_cmd_args_utils(char *src, int *i, int *n)
{
	if ((src[(*i)] != ' ') && (src[(*i)] != '\t') && (src[(*i)] != '\'')
		&& (src[(*i)] != '\"') && (src[(*i)] != '\0'))
	{
		(*n)++;
		while ((src[(*i)] != ' ') && (src[(*i)] != '\t') && (src[(*i)] != '\'')
			&& (src[(*i)] != '\"') && (src[(*i)] != '\0'))
			(*i)++;
	}
	else if (src[(*i)] == '\'')
	{
		(*n)++;
		(*i)++;
		while (src[(*i)] != '\'')
			(*i)++;
	}
	else if (src[(*i)] == '\"')
	{
		(*n)++;
		(*i)++;
		while (src[(*i)] != '\"')
			(*i)++;
	}
}

int	ft_nbr_cmd_args(char *src)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (src[i] != '\0')
	{
		while (((src[i] == ' ') && (src[i] == '\t')) && (src[i] != '\0'))
			i++;
		ft_nbr_cmd_args_utils(src, &i, &n);
		if (src[i] != '\0')
			i++;
	}
	return (n);
}

static char	*ft_put_arg_cmd(char *src, int i, int j)
{
	char	*p;
	int		m;
	int		res;

	m = 0;
	res = i - j;
	p = (char *)malloc(sizeof(char) * (res + 1));
	while (m < res)
	{
		p[m] = src[j];
		m++;
		j++;
	}
	p[m] = '\0';
	return (p);
}

static void	ft_fill_cmd_data_utils(t_arr *tmp_cmd, int *j, int *i, int n)
{
	while (((tmp_cmd[n].comand[(*i)] == ' ')
			|| (tmp_cmd[n].comand[(*i)] == '\t'))
		&& (tmp_cmd[n].comand[(*i)] != '\0'))
		(*i)++;
	(*j) = (*i);
	while (((tmp_cmd[n].comand[(*i)] != ' ')
			&& (tmp_cmd[n].comand[(*i)] != '\t'))
		&& (tmp_cmd[n].comand[(*i)] != '\0'))
	{
		if (tmp_cmd[n].comand[(*i)] == '\'')
		{
			(*i)++;
			while (tmp_cmd[n].comand[(*i)] != '\'')
				(*i)++;
		}
		if (tmp_cmd[n].comand[(*i)] == '\"')
		{
			(*i)++;
			while (tmp_cmd[n].comand[(*i)] != '\"')
				(*i)++;
		}
		(*i)++;
	}
}

void	ft_fill_cmd_data(t_ms_data *data, t_arr *tmp_cmd, int n)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	while (tmp_cmd[n].comand[i] != '\0' && k < data->cmds[n]->nbr_cmd_args)
	{
		ft_fill_cmd_data_utils(tmp_cmd, &j, &i, n);
		tmp = ft_put_arg_cmd(tmp_cmd[n].comand, i, j);
		data->cmds[n]->main_cmd[k] = ft_data_woq(tmp, data);
		free(tmp);
		k++;
		if (tmp_cmd[n].comand[i] != '\0')
			i++;
	}
	data->cmds[n]->main_cmd[k] = NULL;
}
