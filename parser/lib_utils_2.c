/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:58:29 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/07 03:12:37 by mhamdali         ###   ########.fr       */
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

int	ft_atoi(const char *str, t_garbage *gc)
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
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9' )
	{
		result = (result * 10) + str[i] - '0';
		if (result > 255)
			return (ft_putstr_fd("ERROR:\nRGB NUMBRE\n",2), exit(1), -1);
		i++;
	}
	if (str[i] == ' ')
	{
		ft_putstr_fd("ERROR:\nRGB\n",2);
		cleanup_grb_cltr(gc);
		exit(1);
	}
	int result_sign = result * sign;
	if (result_sign < 0)
	{
		ft_putstr_fd("ERROR:\nRGB NUMBRE\n",2);
		cleanup_grb_cltr(gc);
		exit(1);
	}
	return (result_sign);
}
