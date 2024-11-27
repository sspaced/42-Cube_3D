/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:19:03 by lben-adi          #+#    #+#             */
/*   Updated: 2024/08/25 19:21:48 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		j;
	const char	*temp_src;
	char		*temp_dest;

	temp_src = src;
	temp_dest = dest;
	j = 0;
	if (!dest && !src)
		return (NULL);
	while (j < n)
	{
		temp_dest[j] = temp_src[j];
		j++;
	}
	return (dest);
}
