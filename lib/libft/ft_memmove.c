/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:18:55 by loic              #+#    #+#             */
/*   Updated: 2024/08/25 19:23:21 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*cdest;
	const char	*csrc;

	i = n;
	if (!src && !dest)
		return (NULL);
	cdest = dest;
	csrc = src;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (i > 0)
		{
			cdest[i - 1] = csrc[i - 1];
			i--;
		}
	}
	return (dest);
}
