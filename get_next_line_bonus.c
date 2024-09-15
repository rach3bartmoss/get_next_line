/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:35:05 by dopereir          #+#    #+#             */
/*   Updated: 2024/09/15 02:33:03 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_newline_eof(char *buffer)
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

static int	update_remainder_buffer(char **buffer, int newline_pos)
{
	int	remaining_len;

	remaining_len = ft_strlen(*buffer + newline_pos);
	if (remaining_len > 0)
		ft_memmove(*buffer, *buffer + newline_pos, remaining_len + 1);
	else
		(*buffer)[0] = '\0';
	*buffer = ft_realloc(*buffer, ft_strlen(*buffer), remaining_len + 1);
	if (!*buffer)
		return (0);
	return (1);
}

char	*extract_line(char **buffer, int newline_pos)
{
	char	*line;
	int		line_len;

	if ((*buffer)[0] == '\n' && newline_pos >= 0)
	{
		line = malloc(2);
		line[0] = '\n';
		line[1] = '\0';
		if (!update_remainder_buffer(buffer, 1))
			return (free(line), NULL);
		return (line);
	}
	if (newline_pos == -1)
		newline_pos = ft_strlen(*buffer);
	line_len = newline_pos;
	if ((*buffer)[newline_pos] == '\n')
		line_len = newline_pos + 1;
	line = malloc(line_len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *buffer, line_len);
	line[line_len] = '\0';
	if (!update_remainder_buffer(buffer, line_len))
		return (free(line), NULL);
	return (line);
}

int	read_newpiece(int fd, char **buffer)
{
	int			bytes_readed;
	char		current_buffer[BUFFER_SIZE + 1];
	char		*new_buffer;

	bytes_readed = read(fd, current_buffer, BUFFER_SIZE);
	if (bytes_readed <= 0)
		return (bytes_readed);
	current_buffer[bytes_readed] = '\0';
	if (!*buffer)
	{
		*buffer = malloc(1);
		if (!*buffer)
			return (-1);
		(*buffer)[0] = '\0';
	}
	new_buffer = ft_realloc(*buffer, ft_strlen(*buffer),
			ft_strlen(*buffer) + bytes_readed + 1);
	if (!new_buffer)
		return (-1);
	*buffer = new_buffer;
	strncat(*buffer, current_buffer, bytes_readed);
	return (bytes_readed);
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
	while (newline_index == -1 && read_newpiece(fd, &buffer[fd]) > 0)
		newline_index = find_newline_eof(buffer[fd]);
	if (newline_index == -1 && (!buffer[fd] || buffer[fd][0] == '\0'))
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	return (line = extract_line(&buffer[fd], newline_index));
}

/*#define NUM_FILES 3

int main(void)
{
    int fds[NUM_FILES];
    char *filenames[NUM_FILES] = 
		{"1-brouette.txt", "interlinked.txt", "test60.txt"};
    char *line;
    int i;
    int eof_count = 0;

    // Open files
    for (i = 0; i < NUM_FILES; i++)
    {
        fds[i] = open(filenames[i], O_RDONLY);
        if (fds[i] == -1)
        {
            printf("Error opening file: %s\n", filenames[i]);
            exit(1);
        }
    }

    // Read from files alternately
    while (eof_count < NUM_FILES)
    {
        for (i = 0; i < NUM_FILES; i++)
        {
            line = get_next_line(fds[i]);
            if (line)
            {
                printf("File %d: %s", i + 1, line);
                free(line);
            }
            else
            {
                eof_count++;
                close(fds[i]);
                fds[i] = -1;
            }
        }
    }

    return 0;
}*/