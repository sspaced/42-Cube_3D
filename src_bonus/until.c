/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   until.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/18 15:26:36 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_strlen_until(char *str, char until)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == until)
			break ;
		i++;
	}
	return (i);
}

char	*ft_strdup_until(char *str, char until)
{
	char	*str_b;
	int		str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen_until((char *)str, until);
	str_b = (char *)malloc(str_len * sizeof(char) + 1);
	if (!str_b)
		return (NULL);
	while (*str)
	{
		if (*str == until)
			break ;
		*str_b++ = *str++;
	}
	*str_b = '\0';
	return (str_b -= str_len);
}
