/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:54:14 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/07 00:58:56 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"



t_garbage	*gc_init(void)
{
	t_garbage	*g_c;

	g_c = malloc(sizeof(t_garbage));
	if (!g_c)
		return (NULL);
	g_c->blk = NULL;
	g_c->count = 0;
	g_c->append = 0;
	return (g_c);
}

void	*g_malloc(t_garbage *g_c, size_t size)
{
	t_blk	*blk;
	void	*ptr;

	if (!g_c)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	blk = malloc(sizeof(t_blk));
	if (!blk)
		return (free(ptr), NULL);
	blk->ptr = ptr;
	blk->next = g_c->blk;
	g_c->blk = blk;
	g_c->count++;
	return (ptr);
}

char	*g_strdup(t_garbage *g_c, const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = g_malloc(g_c, len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}


void	g_free_one_ptr(t_garbage *g_c, void *ptr)
{
	t_blk	*current;
	t_blk	*previous;

	if (!ptr || !g_c)
		return ;
	previous = NULL;
	current = g_c->blk;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (previous)
				previous->next = current->next;
			else
				g_c->blk = current->next;
			free(ptr);
			free(current);
			g_c->count--;
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	cleanup_grb_cltr(t_garbage *g_c)
{
	t_blk	*current;
	t_blk	*next;

	if (!g_c)
		return ;
	current = g_c->blk;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		current->ptr = NULL;
		free(current);
		current = NULL;
		current = next;
	}
	g_c->blk = NULL;
	g_c->count = 0;
	free(g_c);
	g_c = NULL;
}