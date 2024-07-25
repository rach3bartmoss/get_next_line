/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rache <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:13:48 by rache             #+#    #+#             */
/*   Updated: 2024/07/25 22:23:32 by rache            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file_info	*get_file_info(t_file_info **head, int fd)
{
	t_file_info	*current;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	add_file_info(t_file_info **head, int fd)
{
	t_file_info	*new_node;

	new_node = malloc(sizeof(t_file_info));
	if (!new_node)
		return ;
	new_node->fd = fd;
	new_node->buffer = malloc(BUFFER_SIZE + 1);
	if (!new_node->buffer)
	{
		free(new_node);
		return ;
	}
	new_node->position = 0;
	new_node->b_readed = 0;
	new_node->next = *head;
	*head = new_node;
}

void	remove_file_info(t_file_info **head, int fd)
{
	t_file_info	*current;
	t_file_info	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->buffer);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
