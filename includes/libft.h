/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 10:51:34 by lbenedar          #+#    #+#             */
/*   Updated: 2021/09/15 23:01:35 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char	*ft_replace(const char *main, const char *sample, const char *value);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strljoin(char const *s1, char const *s2, size_t len_s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strcpy(char *dst, const char *src);
char	*ft_strndup(const char *s, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	**ft_clean_split(char **array);
void	ft_bzero(void *s, size_t n);
void	ft_putstr(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
int		ft_strcmp(char *str_1, char *str_2);
char	**ft_split_one(char *str, char c);
long	ft_atoi(const char *nptr);

#endif
