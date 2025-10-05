/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:12:24 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/05 16:34:44 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (fd < 0 || s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*a1;
	unsigned char	*a2;

	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	if (!a1 && !a2)
		return (0);
	i = 0;
	while (a1[i] || a2[i])
	{
		if (a1[i] != a2[i])
			return (a1[i] - a2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2, t_garbage *gc)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		return (g_strdup(gc, s2));
	else if (*s2 == '\0')
		return (g_strdup(gc, "\0"));
	result = ((char *)g_malloc (gc, ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!result)
		return (NULL);
	ft_strlcpy (result, s1, ft_strlen(s1) + 1);
	ft_strlcat (result, s2, ft_strlen(result) + ft_strlen(s2) + 1);
	return (result);
}
