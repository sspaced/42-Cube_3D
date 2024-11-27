/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:52:11 by loic              #+#    #+#             */
/*   Updated: 2024/08/25 19:21:55 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *mem, int c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (*(const unsigned char *)(mem + i) == (const unsigned char)c)
			return ((void *)(mem + i));
		i++;
	}
	return (NULL);
}
