/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:11:25 by loic              #+#    #+#             */
/*   Updated: 2024/09/22 18:51:08 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = i;
		k = 0;
		while (needle[k] != '\0' && needle[k] == haystack[j] && j < len)
		{
			k++;
			j++;
		}
		if (needle[k] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
