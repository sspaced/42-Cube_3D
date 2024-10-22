/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:27:38 by lben-adi          #+#    #+#             */
/*   Updated: 2024/09/22 22:41:13 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strncpy(char *dest, char *src, int len)
{
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	if (!dest)
		return (NULL);
	if (len <= 0)
		return (NULL);
	while (src[i] && (i < len))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
