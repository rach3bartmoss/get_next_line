/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:29:34 by dopereir          #+#    #+#             */
/*   Updated: 2024/09/15 22:32:33 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	*ft_realloc(void *ptr, size_t oldsize, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_strlen(char *str);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
char	*get_next_line(int fd);
#endif
