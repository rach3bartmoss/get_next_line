/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:35:05 by dopereir          #+#    #+#             */
/*   Updated: 2024/09/07 15:41:44 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_newline_eof(char *buffer)/*Newline found, return its position*/
{
	int	i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
// No newline found

char	*expand_buffer(char *buffer, size_t new_size)//resize the chunk
{
	char	*new_buffer;

	new_buffer = ft_realloc(buffer, new_size + 1);
	if (!new_buffer)
		return (NULL);
	return (new_buffer);
}

char	*extract_line(char **buffer, int newline_index)//extract line from buf
{
	char	*line;
	int		rem_len;

	if (newline_index == -1)
		newline_index = ft_strlen(*buffer);
	line = malloc(newline_index + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *buffer, newline_index);
	line[newline_index] = '\0';
	if ((*buffer)[newline_index] == '\n')
		newline_index++;
	rem_len = ft_strlen(*buffer + newline_index);
	ft_memmove(*buffer, *buffer + newline_index, rem_len + 1);
	*buffer = ft_realloc(*buffer, rem_len + 1);
	if (!*buffer)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	read_chunk(int fd, char **buffer) //reads a piece(chunk), a dym alloc space
{
	char	temp_buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*new_buffer;

	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	temp_buffer[bytes_read] = '\0';
	new_buffer = expand_buffer(*buffer, ft_strlen(*buffer) + bytes_read);
	if (!new_buffer)
		return (-1);
	*buffer = new_buffer;
	ft_strcat(*buffer, temp_buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;
	int			newline_index;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	newline_index = find_newline_eof(buffer[fd]);
	while (newline_index == -1 && read_chunk(fd, &buffer[fd]) > 0)
		newline_index = find_newline_eof(buffer[fd]);
	if (!buffer[fd][0])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	return (line = extract_line(&buffer[fd], newline_index));
}
