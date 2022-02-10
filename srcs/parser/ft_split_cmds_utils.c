/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:23:56 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/18 12:58:58 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nbr_pipes_in_str(char *str)
{
	int	i;
	int	res;
	int	q;
	int	qq;

	i = 0;
	q = 0;
	qq = 0;
	res = 1;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			ft_check_quotes(str[i], &q, &qq);
		if ((str[i] == '|') && (q == 0) && (qq == 0))
			res++;
		i++;
	}
	return (res);
}

static char	*ft_put_cmd(char *str, int i, int j)
{
	int		k;
	char	*p;

	k = 0;
	p = (char *)malloc(sizeof(char) * ((i - j) + 1));
	while (j < i)
	{
		p[k] = str[j];
		j++;
		k++;
	}
	p[k] = '\0';
	return (p);
}

void	ft_split_cmds(char ***arr, char *str)
{
	int	i;
	int	q;
	int	qq;
	int	n;
	int	j;

	i = 0;
	q = 0;
	qq = 0;
	n = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			ft_check_quotes(str[i], &q, &qq);
		if ((str[i] == '|') && (q == 0) && (qq == 0))
		{
			(*arr)[n] = ft_put_cmd(str, i, j);
			i++;
			j = i;
			n++;
		}
		i++;
	}
	(*arr)[n] = ft_put_cmd(str, i, j);
}

char	*ft_data_woq(char *src, t_ms_data *data)
{
	char	*ptr;

	ptr = ft_str_woq(data, src);
	return (ptr);
}

void	ft_join_split(int j, int i, char **p, char *src)
{
	int		n;
	char	*ptr;
	int		res;

	n = 0;
	res = i - j;
	ptr = (char *)malloc(sizeof(char) * (strlen_p(*p) + res + 1));
	while (n < strlen_p(*p))
	{
		ptr[n] = (*p)[n];
		n++;
	}
	while (n < (res + strlen_p(*p)))
	{
		ptr[n] = src[j];
		j++;
		n++;
	}
	ptr[n] = '\0';
	free(*p);
	(*p) = ptr;
}
