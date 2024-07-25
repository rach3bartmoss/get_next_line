/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:30:19 by rache             #+#    #+#             */
/*   Updated: 2024/07/25 22:57:02 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <unistd.h>

static char	*resize_line_buffer(char *line, int new_size)
{
	char	*new_line;

	new_line = realloc(line, new_size);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	return (new_line);
}

static char	*read_next_block(t_file_info *file, int *b_written)
{
	int		j;
	char	*line;

	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (1)
	{
		if (file->position >= file->b_readed)
		{
			file->b_readed = read(file->fd, file->buffer,
					BUFFER_SIZE);
			if (file->b_readed <= 0)
				break ;
			file->position = 0;
		}
		line[j++] = file->buffer[file->position++];
		if (file->buffer[file->position - 1] == '\n'
				|| file->buffer[file->position - 1] == '\0')
			break ;
		if (j >= BUFFER_SIZE)
		{
			line = resize_line_buffer(line, j + BUFFER_SIZE + 1);
			if (!line)
				return (NULL);
		}
	}
	line[j] = '\0';
	*b_written = j;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_file_info	*file_list;
	t_file_info			*file;
	int					bytes_written;
	char				*line;

	file_list = NULL;
	file = get_file_info(&file_list, fd);
	bytes_written = 0;
	line = read_next_block(file, &bytes_written);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!file)
	{
		add_file_info(&file_list, fd);
		file = get_file_info(&file_list, fd);
	}
	if (file->b_readed <= 0 && bytes_written == 0)
	{
		free(line);
		remove_file_info(&file_list, fd);
		return (NULL);
	}
	return (line);
}
/*int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Usage: ./program filename\n", 26);
		return 1;
	}
	
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error opening file\n", 19);
		return 1;
	}
	char *line;
	while ((line = get_next_line(fd)))
	{
		write(1, line, strlen(line));
		free(line);
	}
	close(fd);
	return 0;
}*/
