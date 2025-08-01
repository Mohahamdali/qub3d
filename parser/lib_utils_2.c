/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:58:29 by mhamdali          #+#    #+#             */
/*   Updated: 2025/07/31 22:07:11 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;
	size_t	space_left;

	i = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (size == 0)
		return (src_len);
	if (dest_len >= size)
		return (size + src_len);
	space_left = size - dest_len - 1;
	while (src[i] != '\0' && i < space_left)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || ft_isalpha(c) != 0)
	{
		return (1);
	}
	return (0);
}


static int	handle_overflow(unsigned long result, int sign)
{
	if ((result >= 9223372036854775807) && sign == 1)
		return (-1);
	else if (result >= 9223372036854775807 && sign == -1)
		return (0);
	return (result);
}

int	ft_atoi(const char *str)
{
	unsigned long		result;
	size_t				i;
	int					sign;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		if (result >= 9223372036854775807)
			return (handle_overflow(result, sign));
		i++;
	}
	return ((int)result * sign);
}
