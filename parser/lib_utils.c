/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:01:23 by mhamdali          #+#    #+#             */
/*   Updated: 2025/07/31 22:07:03 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../qub3d.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	result = ((char *)malloc (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!result)
		return (NULL);
	ft_strlcpy (result, s1, ft_strlen(s1) + 1);
	ft_strlcat (result, s2, ft_strlen(result) + ft_strlen(s2) + 1);
	return (result);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] != '\0' && str1[i] == str2[i] && i < n - 1)
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	length_source;
	size_t	i;

	i = 0;
	length_source = ft_strlen(src);
	if (dest_size == 0)
		return (length_source);
	while (src[i] != '\0' && i < dest_size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (length_source);
}

