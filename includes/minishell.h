/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:48:17 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/20 14:55:49 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <linux/limits.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

# define CLR_STR "\033[2J\033[1;1H"
# define READ_PIPE 0
# define WRITE_PIPE 1

typedef enum e_redir
{
	none,
	redirect_i,
	redirect_o,
	redirect_a,
	redirect_d
}				t_redir;

typedef struct s_piped_io
{
	int	i_dup;
	int	o_dup;
	int	e_dup;
	int	fd_in[2];
	int	fd_out[2];
	int	fd_e[2];
}				t_piped_io;

typedef struct s_refile
{
	char	*filename;
	t_redir	type;
}				t_refile;

typedef struct s_cmd
{
	char		**main_cmd;
	t_refile	**redirect;
	int			nbr_cmd_args;
	int			nbr_redir;
}				t_cmd;

typedef struct s_usable_redir
{
	t_refile	*input;
	t_refile	*last_d;
	t_refile	*output;
	char		*filename_err;
	int			fd_out;
	int			fd_in;
	int			fd_delim[2];
}				t_usable_redir;

typedef struct s_tmp
{
	int			i;
	int			j;
	int			nq;
	int			ndlr;
	int			prev_return;
}				t_tmp;

typedef struct s_arr
{
	char	*comand;
	char	*red;
}				t_arr;

typedef struct s_env_content
{
	char				*var_name;
	char				*var_value;
}						t_env_content;

typedef struct s_ms_data
{
	char				*ps1_sample;
	char				*ps2_sample;
	char				*ps1_print;
	char				*ps2_print;
	char				*username;
	char				*v_shell;
	char				*old_dir;
	char				*curr_dir;
	char				*home_dir;
	char				*shell_name;
	t_env_content		**envp;
	t_cmd				**cmds;
	int					prev_return;
	int					nbr_cmds;
}						t_ms_data;

void			run_shell(char **envp);
void			sigint_handler(int signum);
void			read_content(t_ms_data *data);
void			draw_shell(t_ms_data *data);
void			check_seq(t_ms_data *data);
void			out_fd(t_piped_io *desc);
int				setup_fd(t_piped_io *desc, t_ms_data *data, int i);
void			read_fd(int fd, int fd_out);
int				setup_io(t_ms_data *data, t_usable_redir *redirs,
					t_piped_io *desc);
int				out_error(t_ms_data *data, char *error, char *cmd);
void			check_error(void);
void			ft_free_arr(void **arr);
void			free_cmds(t_ms_data *data);
void			free_redirs(t_usable_redir *redir);
void			ft_free_sorted(t_env_content **arr);
void			free_env(t_env_content **env);
void			set_env(t_ms_data *data, char **envp);
t_env_content	**sort_env(t_env_content **envp);
int				ft_size_arr(void **arr);
char			**env_to_str(t_env_content **content);
int				find_command(t_ms_data *data, t_cmd *cmd);
void			exec_command(t_ms_data *data, t_cmd *cmd,
					t_usable_redir *redirs, t_piped_io *desc);
int				exec_file(char **cmd_arr, t_ms_data *data, t_piped_io *desc,
					t_usable_redir *redirs);
int				exec_echo(char **cmd, t_usable_redir *redirs);
void			exec_exit(char **cmd, t_ms_data *data);
int				exec_pwd(t_ms_data *data);
int				exec_cd(t_cmd *cmd, t_ms_data *data, t_usable_redir *redirs);
int				exec_export(char **args, t_ms_data *data);
int				exec_env(t_ms_data *data);
int				exec_unset(char **args, t_ms_data *data);
/*parser*/
void			ft_check_quotes(char chr, int *q, int *qq);
int				ft_check_str(char *str);
char			*ft_itoa_pars(int n);
void			ft_get_data(t_ms_data *data, t_arr *tmp_cmd);
int				ft_nbr_redir(char *src);
void			ft_fill_redir_data(t_ms_data *data, t_arr *tmp_cmd, int n);
int				ft_nbr_pipes_in_str(char *str);
void			ft_split_cmds(char ***arr, char *str);
char			*ft_data_woq(char *src, t_ms_data *data);
void			ft_join_split(int j, int i, char **p, char *src);
void			ft_redir_pull(t_tmp *tmp, char *src);
char			*ft_fill_tmp_redir(char *src);
char			*ft_fill_tmp_cmd(char *src);
void			ft_get_env(int prev_return, char **env, t_ms_data *data);
void			ft_join_env(char **ptr, char *env);
char			*ft_str_woq(t_ms_data *data, char *str);
int				strlen_p(char *str);
int				strcmp_p(char *p, char *tmp_env);
char			*strcpy_p(char *src);
void			ft_strjoin_pars(char *str, t_tmp *tmp, char **ptr);
char			*ft_rmvdlr_utils(int n, char *str, t_tmp *tmp);
int				parser(char *str, t_ms_data *data);
int				ft_nbr_cmd_args(char *src);
void			ft_fill_cmd_data(t_ms_data *data, t_arr *tmp_cmd, int n);

#endif
