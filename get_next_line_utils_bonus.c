/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:42:20 by dopereir          #+#    #+#             */
/*   Updated: 2024/09/15 02:19:12 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	*ft_realloc(void *ptr, size_t oldsize, size_t size)
{
	void	*new;
	size_t	minsize;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));
	new = malloc(size);
	if (!new)
		return (NULL);
	minsize = size;
	if (oldsize < size)
		minsize = oldsize;
	ft_memcpy(new, ptr, minsize);
	while (size - oldsize != 0)
		((char *)new)[oldsize++] = '\0';
	free(ptr);
	return (new);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tempsrc;
	unsigned char	*tempdest;

	tempsrc = (unsigned char *)src;
	tempdest = (unsigned char *)dest;
	while (n--)
	{
		*tempdest++ = *tempsrc++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (s < d && d < s + n)
	{
		d = d + n - 1;
		s = s + n - 1;
		while (n--)
			*d-- = *s--;
	}
	else
		while (n--)
			*d++ = *s++;
	return (dest);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < nb)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
