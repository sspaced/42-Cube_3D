/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:55:08 by loic              #+#    #+#             */
/*   Updated: 2024/08/25 19:21:27 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *str1, const void *str2, size_t size)
{
	while (size--)
	{
		if (*(unsigned char *)str1 != *(unsigned char *)str2)
			return (*(unsigned char *)str1 - *(unsigned char *)str2);
		++str1;
		++str2;
	}
	return (0);
}
