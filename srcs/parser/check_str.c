/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 21:11:54 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/14 23:39:45 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_quotes(char chr, int *q, int *qq)
{
	if ((chr == '\'') && (*qq == 0) && (*q == 0))
		*q = 1;
	else if ((chr == '\'') && (*qq == 0) && (*q == 1))
		*q = 0;
	else if ((chr == '\"') && (*q == 0) && (*qq == 0))
		*qq = 1;
	else if ((chr == '\"') && (*q == 0) && (*qq == 1))
		*qq = 0;
}

int	ft_check_str(char *str)
{
	int	i;
	int	q;
	int	qq;

	i = 0;
	q = 0;
	qq = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			ft_check_quotes(str[i], &q, &qq);
		i++;
	}
	if ((q == 1) || (qq == 1))
		return (1);
	return (0);
}

static int	ft_len(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_pars(int n)
{
	char	*p;
	int		l;
	int		k;

	l = ft_len(n);
	k = 1;
	p = (char *)malloc(sizeof(char) * (l + 1));
	if (p == NULL)
		return (NULL);
	if (n < 0)
		k = -1;
	p[l] = '\0';
	l--;
	while (l >= 0)
	{
		p[l] = ((n % 10) * k) + 48;
		n = n / 10;
		l--;
	}
	if (k < 0)
		p[0] = '-';
	return (p);
}
