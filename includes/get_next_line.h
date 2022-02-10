/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:15:28 by lbenedar          #+#    #+#             */
/*   Updated: 2021/03/26 19:21:49 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

int		get_next_line(int fd, char **line);
size_t	find_end_line(const char *str);
char	*ft_strdup_line(const char *s);
char	*skip_line(char *s);
char	*strcat_newline(char **dst, const char *src);

#endif
