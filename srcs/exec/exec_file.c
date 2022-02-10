/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:41:42 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/16 20:58:42 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_all_fd(t_piped_io *desc, t_usable_redir *redirs)
{
	close(desc->fd_e[0]);
	if (desc->fd_in[0])
		close(desc->fd_in[0]);
	if (redirs->fd_delim[0])
		close(redirs->fd_delim[0]);
	if (desc->fd_out[0])
		close(desc->fd_out[0]);
	if (desc->fd_out[1])
		close(desc->fd_out[1]);
	close(desc->o_dup);
}

static int	forked_exec(char **cmd_arr, t_ms_data *data, t_piped_io *desc,
t_usable_redir *redirs)
{
	char	**envp;

	envp = env_to_str(data->envp);
	dup2(redirs->fd_in, 0);
	close_all_fd(desc, redirs);
	execve(cmd_arr[0], cmd_arr, envp);
	ft_free_arr((void *)envp);
	return (errno);
}

int	exec_file(char **cmd_arr, t_ms_data *data, t_piped_io *desc,
t_usable_redir *redirs)
{
	int	pid;
	int	stat_loc;
	int	res;

	pid = fork();
	if (!pid)
	{
		res = forked_exec(cmd_arr, data, desc, redirs);
		exit(res);
	}
	else if (pid > 0)
		waitpid(0, &stat_loc, 0);
	data->prev_return = WEXITSTATUS(stat_loc);
	errno = 0;
	return (0);
}
