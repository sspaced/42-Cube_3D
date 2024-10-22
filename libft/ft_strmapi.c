/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:57:50 by loic              #+#    #+#             */
/*   Updated: 2024/09/06 00:02:56 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	str_len;
	char	*str_b;
	size_t	i;

	str_len = ft_strlen(s);
	i = 0;
	if (str_len == 0)
	{
		str_b = (char *)malloc(1);
		if (!str_b)
			return (NULL);
		*str_b = '\0';
		return (str_b);
	}
	str_b = (char *)malloc(str_len + 1);
	if (!str_b)
		return (NULL);
	while (*s)
	{
		*str_b++ = (*f)(i, *s++);
		i++;
	}
	*str_b = '\0';
	return (str_b - str_len);
}
