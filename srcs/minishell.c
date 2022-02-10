/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:37:03 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/17 15:30:53 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_data(t_ms_data *data)
{
	char	*temp;

	data->ps1_sample = 0;
	data->ps2_sample = 0;
	data->ps1_print = 0;
	data->ps2_print = 0;
	data->prev_return = 0;
	data->shell_name = ft_strdup("minishell");
	data->username = ft_strdup("lb|bc");
	data->v_shell = ft_strdup("1.0001");
	if (getenv("HOME"))
		data->home_dir = ft_strdup(getenv("HOME"));
	else
		errno = EFAULT;
	if (getenv("PWD"))
		data->old_dir = ft_strdup(getenv("PWD"));
	else
		errno = EFAULT;
	if (errno)
		return ;
	temp = ft_replace(getenv("PWD"), data->home_dir, "~");
	data->curr_dir = temp;
}

static void	clear_data(t_ms_data *data)
{
	if (data->ps1_print)
		free(data->ps1_print);
	if (data->ps1_sample)
		free(data->ps1_sample);
	if (data->ps2_sample)
		free(data->ps2_sample);
	if (data->username)
		free(data->username);
	if (data->v_shell)
		free(data->v_shell);
	if (data->curr_dir)
		free(data->curr_dir);
	if (data->shell_name)
		free(data->shell_name);
	if (data->home_dir)
		free(data->home_dir);
	if (data->old_dir)
		free(data->old_dir);
}

/*
**	Start shell without variables
**	TODO: peredat copiu nvp v data
*/

void	run_shell(char **envp)
{
	t_ms_data	data;

	if (envp)
		NULL;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	set_data(&data);
	check_error();
	set_env(&data, envp);
	check_error();
	read_content(&data);
	check_error();
	draw_shell(&data);
	clear_data(&data);
}
