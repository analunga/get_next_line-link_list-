/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analunga <analunga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 23:27:46 by analunga          #+#    #+#             */
/*   Updated: 2024/05/21 04:20:26 by analunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_from_file(int fd, t_gnl_vars *vars)
{
	vars->bytes_read = read(fd, vars->buffer, BUFFER_SIZE);
	if (vars->bytes_read == -1)
	{
		vars->bytes_read = 0;
		vars->buffer[0] = '\0';
		vars->remainder[0] = '\0';
		return (NULL);
	}
	else if (vars->bytes_read == 0)
		return (NULL);
	vars->buffer[vars->bytes_read] = '\0';
	return (vars->buffer);
}

static char	*get_line(t_gnl_vars *vars)
{
	vars->line = ft_strdup(vars->remainder);
	if (!vars->line)
		return (NULL);
	vars->ptr_n = ft_strchr(vars->line, '\n');
	return (vars->line);
}

static void	update_remainder(t_gnl_vars *vars)
{
	size_t	len;

	len = ft_strlen(vars->ptr_n + 1);
	ft_memmove(vars->remainder, vars->ptr_n + 1, len + 1);
}

char	*get_next_line(int fd)
{
	static t_gnl_vars	vars = {{0}, NULL, NULL, {0}, NULL, 0};
	char				*line;
	size_t				line_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!vars.line && !(get_line(&vars)))
		return (NULL);
	while (!vars.ptr_n && read_from_file(fd, &vars))
	{
		if (vars.bytes_read < 0 || vars.bytes_read == -1)
		{
			free(vars.line);
			vars.line = NULL;
			return (NULL);
		}
		vars.temp = ft_strjoin(vars.line, vars.buffer);
		free(vars.line);
		if (!vars.temp)
		{
			return (NULL);
		}
		vars.line = vars.temp;
		vars.ptr_n = ft_strchr(vars.line, '\n');
	}
	if (!vars.ptr_n)
	{
		if (vars.line && *(vars.line))
		{
			line_len = ft_strlen(vars.line);
			line = (char *)malloc((line_len + 1) * sizeof(char));
			if (!line)
			{
				free(vars.line);
				vars.line = NULL;
				return (NULL);
			}
			ft_memmove(line, vars.line, line_len);
			line[line_len] = '\0';
			free(vars.line);
			vars.line = NULL;
			vars.remainder[0] = '\0';
			return (line);
		}
		else
		{
			free(vars.line);
			vars.line = NULL;
			return (NULL);
		}
	}
	line = (char *)malloc((vars.ptr_n - vars.line + 2) * sizeof(char));
	if (!line)
	{
		free(vars.line);
		vars.line = NULL;
		return (NULL);
	}
	ft_memmove(line, vars.line, vars.ptr_n - vars.line + 1);
	line[vars.ptr_n - vars.line + 1] = '\0';
	update_remainder(&vars);
	free(vars.line);
	vars.line = NULL;
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("example.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }