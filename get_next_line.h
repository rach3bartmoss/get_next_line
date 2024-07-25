/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:55:30 by rache             #+#    #+#             */
/*   Updated: 2024/07/25 22:30:19 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_file_info
{
	char				*buffer;
	int					fd;
	int					position;
	int					b_readed;
	struct s_file_info	*next;
}		t_file_info;

char		*get_next_line(int fd);
t_file_info	*get_file_info(t_file_info **head, int fd);
void		add_file_info(t_file_info **head, int fd);
void		remove_file_info(t_file_info **head, int fd);

#endif
