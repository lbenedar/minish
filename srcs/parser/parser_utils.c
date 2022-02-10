/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:24:53 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/14 23:40:32 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_p(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	strcmp_p(char *p, char *tmp_env)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (tmp_env[i] != '\0')
	{
		if (tmp_env[i] != p[i])
		{
			res = 1;
			break ;
		}
		i++;
	}
	return (res);
}

char	*strcpy_p(char *src)
{
	char	*p;
	int		n;
	int		i;

	i = 0;
	n = strlen_p(src);
	p = (char *)malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	ft_strjoin_pars(char *str, t_tmp *tmp, char **ptr)
{
	int		n;
	char	*p;

	n = 0;
	p = (char *)malloc(sizeof(char) * ((tmp->i - tmp->j) + strlen_p(*ptr) + 1));
	while (n < strlen_p(*ptr))
	{
		p[n] = (*ptr)[n];
		n++;
	}
	while (n < (tmp->i - tmp->nq - tmp->ndlr))
	{
		p[n] = str[tmp->j];
		n++;
		tmp->j++;
	}
	p[n] = '\0';
	free(*ptr);
	*ptr = p;
}

char	*ft_rmvdlr_utils(int n, char *str, t_tmp *tmp)
{
	char	*p;
	int		r;

	r = 0;
	p = (char *)malloc(sizeof(char) * (n + 1));
	while (tmp->j < tmp->i)
	{
		p[r] = str[tmp->j];
		r++;
		tmp->j++;
	}
	p[r] = '\0';
	return (p);
}
