/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analunga <analunga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:37:27 by analunga          #+#    #+#             */
/*   Updated: 2024/05/18 14:57:59 by analunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_gnl_vars
{
	char	remainder[BUFFER_SIZE + 1];
	char	*line;
	char	*ptr_n;
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes_read;
}	t_gnl_vars;

char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
void	ft_memmove(void *dest, const void *src, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
char	*get_next_line(int fd);

#endif
