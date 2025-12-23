/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:55:46 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/19 14:48:59 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
typedef struct s_gnl
{
	char			*stash;
	char			*line;
	char			*buffer;
}					t_gnl;

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
size_t				ft_strlcat(char *dest, char *src, size_t size);
size_t				ft_strlcpy(char *dest, char *src, size_t size);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
void				*ft_memmove(void *dest, const void *src, size_t n);
int					ft_atoi(const char *nptr);
int					ft_atoi_safe(const char *nptr, int *out);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
char				*ft_utoa(unsigned int n);
char				*ft_itoa_base(unsigned long n, int base);
int					ft_atoi_base(const char *str, int str_base);
// functions for printf
int					ft_is_valid_specifier(char c);
int					ft_scan(char specifier, va_list args);
int					ft_process_string(char *ptr, va_list args);
int					ft_handle_int(int num);
int					ft_handle_unsigned_int(unsigned int num);
int					ft_handle_hexadecimal(unsigned int num, char c);
int					ft_handle_percentage(void);
int					ft_handle_string(char *string);
int					ft_handle_character(char c);
int					ft_handle_pointer(void *ptr);
int					ft_printf(const char *string, ...);
char				**ft_split_quote(const char *s, char c, int i, int j);
// gnl
char				*get_next_line(int fd, int flush);
int					ft_read(int fd, char **stash, char **buffer);
void				ft_update_stash(char **stash);
char				*ft_get_line(char *stash);
void				*free_two(char **ptr1, char **ptr2);

#endif
