/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:24:09 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/14 23:40:14 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_pull(t_tmp *tmp, char *src)
{
	while (((src[tmp->i] == '<') || (src[tmp->i] == '>'))
		&& (src[tmp->i] != '\0'))
		tmp->i++;
	while (((src[tmp->i] == ' ') || (src[tmp->i] == '\t'))
		&& (src[tmp->i] != '\0'))
		tmp->i++;
	if (src[tmp->i] == '\'')
	{
		tmp->i++;
		while ((src[tmp->i] != '\'') && (src[tmp->i] != '\0'))
			tmp->i++;
		tmp->i++;
	}
	else if (src[tmp->i] == '\"')
	{
		tmp->i++;
		while ((src[tmp->i] != '\"') && (src[tmp->i] != '\0'))
			tmp->i++;
		tmp->i++;
	}
	else
		while (((src[tmp->i] != ' ') && (src[tmp->i] != '\t'))
			&& (src[tmp->i] != '\0'))
			tmp->i++;
}

static void	ft_fill_tmp_redir_utils(t_tmp *tmp, char *src, char **p)
{
	tmp->j = tmp->i;
	ft_redir_pull(tmp, src);
	ft_join_split(tmp->j, tmp->i, p, src);
	if ((src[tmp->i] == '>') || (src[tmp->i] == '<'))
		tmp->i--;
}

char	*ft_fill_tmp_redir(char *src)
{
	t_tmp	tmp;
	int		q;
	int		qq;
	char	*p;

	q = 0;
	qq = 0;
	tmp.i = 0;
	tmp.j = 0;
	p = strcpy_p("");
	while (src[tmp.i] != '\0')
	{
		if ((src[tmp.i] == '\'') || (src[tmp.i] == '\"'))
			ft_check_quotes(src[tmp.i], &q, &qq);
		if (((src[tmp.i] == '<') || (src[tmp.i] == '>'))
			&& (q == 0) && (qq == 0))
			ft_fill_tmp_redir_utils(&tmp, src, &p);
		if (src[tmp.i] != '\0')
			tmp.i++;
	}
	return (p);
}

static void	ft_fill_tmp_cmd_utils(t_tmp *tmp, char *src, char **p)
{
	ft_join_split(tmp->j, tmp->i, p, src);
	ft_redir_pull(tmp, src);
	tmp->j = tmp->i;
	if ((src[tmp->i] == '>') || (src[tmp->i] == '<'))
		tmp->i--;
}

char	*ft_fill_tmp_cmd(char *src)
{
	t_tmp	tmp;
	int		q;
	int		qq;
	char	*p;

	q = 0;
	qq = 0;
	tmp.i = 0;
	tmp.j = 0;
	p = strcpy_p("");
	while (src[tmp.i] != '\0')
	{
		if ((src[tmp.i] == '\'') || (src[tmp.i] == '\"'))
			ft_check_quotes(src[tmp.i], &q, &qq);
		if (((src[tmp.i] == '<') || (src[tmp.i] == '>'))
			&& (q == 0) && (qq == 0))
			ft_fill_tmp_cmd_utils(&tmp, src, &p);
		if (src[tmp.i] != '\0')
			tmp.i++;
	}
	ft_join_split(tmp.j, tmp.i, &p, src);
	return (p);
}
