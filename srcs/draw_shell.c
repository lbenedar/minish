/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:46:29 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/18 15:50:17 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_colors(char **print, char *sample, int *i)
{
	char	*subprint;

	if ((sample[*i + 1] == '0' && sample[*i + 2] == '3'
			&& sample[*i + 3] == '3') || (sample[*i + 1] == 'e'))
	{
		subprint = ft_strljoin(*print, sample, *i);
		free(*print);
		*print = subprint;
		subprint = ft_strjoin(*print, "\033");
		free(*print);
		*print = subprint;
		sample = sample + (*i + 4);
		*i = -1;
	}
	return (sample);
}

static char	*check_values(t_ms_data *data, char **print,
							char *sample, int *i)
{
	char	*subprint;

	if (sample[*i + 1] == 's' || sample[*i + 1] == 'u'
		|| sample[*i + 1] == 'v' || sample[*i + 1] == 'w')
	{
		subprint = ft_strljoin(*print, sample, *i);
		free(*print);
		*print = subprint;
		subprint = 0;
		if (sample[*i + 1] == 's')
			subprint = ft_strjoin(*print, data->shell_name);
		else if (sample[*i + 1] == 'u')
			subprint = ft_strjoin(*print, data->username);
		else if (sample[*i + 1] == 'v')
			subprint = ft_strjoin(*print, data->v_shell);
		else if (sample[*i + 1] == 'w')
			subprint = ft_strjoin(*print, data->curr_dir);
		free(*print);
		*print = subprint;
		sample = sample + (*i + 2);
		*i = -1;
	}
	sample = check_colors(print, sample, i);
	return (sample);
}

static char	*parse_ps(char **print, char *sample, t_ms_data *data)
{
	int		i;
	char	*subprint;

	if (*print)
		free(*print);
	*print = ft_strdup("");
	i = -1;
	while (sample[++i])
	{
		if (sample[i] == '\\')
			sample = check_values(data, print, sample, &i);
	}
	subprint = ft_strjoin(*print, sample);
	free(*print);
	*print = subprint;
	return (*print);
}

static int	event_do_nothing(void)
{
	return (0);
}

/*
**	Function that draw prompt, waiting to read commands
**	and than execute that commands
*/

void	draw_shell(t_ms_data *data)
{
	char	*line;

	rl_event_hook = event_do_nothing;
	while (1)
	{
		parse_ps(&(data->ps1_print), data->ps1_sample, data);
		rl_done = 0;
		rl_on_new_line();
		line = readline(data->ps1_print);
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		if (!(ft_memcmp(line, "\x18", 2)) || ft_check_str(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		parser(line, data);
		check_seq(data);
		free_cmds(data);
		free(line);
	}
}
