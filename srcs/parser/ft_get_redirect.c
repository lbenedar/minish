/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:23:26 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/17 23:31:33 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nbr_redir(char *src)
{
	int	i;
	int	n;
	int	q;
	int	qq;

	i = 0;
	n = 0;
	q = 0;
	qq = 0;
	while (src[i] != '\0')
	{
		if ((src[i] == '\'') || (src[i] == '\"'))
			ft_check_quotes(src[i], &q, &qq);
		else if (((src[i] == '>') || (src[i] == '<')) && (q == 0) && (qq == 0))
		{
			n++;
			while (((src[i] == '>') || (src[i] == '<')) && (src[i] != '\0'))
				i++;
			continue ;
		}
		i++;
	}
	return (n);
}

static t_redir	ft_redir_type(char *src, int i)
{
	t_redir	type;

	if ((src[i] == '<') && (src[i + 1] != '<'))
		type = redirect_i;
	if ((src[i] == '>') && (src[i + 1] != '>'))
		type = redirect_o;
	if ((src[i] == '>') && (src[i + 1] == '>'))
		type = redirect_a;
	if ((src[i] == '<') && (src[i + 1] == '<'))
		type = redirect_d;
	return (type);
}

static char	*ft_redir_filename(char *src, int j, int i)
{
	char	*ptr;
	int		n;
	int		res;

	n = 0;
	res = i - j;
	ptr = (char *)malloc(sizeof(char) * (res + 1));
	while (n < res)
	{
		ptr[n] = src[j];
		n++;
		j++;
	}
	ptr[n] = '\0';
	return (ptr);
}

static void	ft_fill_redir_data_utils(t_arr *tmp_cmd, int *j, int *i, int n)
{
	while (((tmp_cmd[n].red[(*i)] == ' ')
			|| (tmp_cmd[n].red[(*i)] == '\t'))
		&& (tmp_cmd[n].red[(*i)] != '\0'))
		(*i)++;
	(*j) = (*i);
	while (((tmp_cmd[n].red[(*i)] != ' ')
			&& (tmp_cmd[n].red[(*i)] != '\t'))
		&& (tmp_cmd[n].red[(*i)] != '\0')
		&& (tmp_cmd[n].red[(*i)] != '<')
		&& (tmp_cmd[n].red[(*i)] != '>'))
	{
		if (tmp_cmd[n].red[(*i)] == '\'')
		{
			(*i)++;
			while (tmp_cmd[n].red[(*i)] != '\'')
				(*i)++;
		}
		if (tmp_cmd[n].red[(*i)] == '\"')
		{
			(*i)++;
			while (tmp_cmd[n].red[(*i)] != '\"')
				(*i)++;
		}
		(*i)++;
	}
}

void	ft_fill_redir_data(t_ms_data *data, t_arr *tmp_cmd, int n)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	while (tmp_cmd[n].red[i] != '\0' && k < data->cmds[n]->nbr_redir)
	{
		data->cmds[n]->redirect[k] = (t_refile *)malloc(sizeof(t_refile) * 1);
		if ((tmp_cmd[n].red[i] == '<') || (tmp_cmd[n].red[i] == '>'))
		{
			data->cmds[n]->redirect[k]->type = ft_redir_type(tmp_cmd[n].red, i);
			while (((tmp_cmd[n].red[i] == '>') || (tmp_cmd[n].red[i] == '<'))
				&& (tmp_cmd[n].red[i] != '\0'))
				i++;
		}
		ft_fill_redir_data_utils(tmp_cmd, &j, &i, n);
		tmp = ft_redir_filename(tmp_cmd[n].red, j, i);
		data->cmds[n]->redirect[k]->filename = ft_data_woq(tmp, data);
		free (tmp);
		k++;
	}
	data->cmds[n]->redirect[k] = NULL;
}
