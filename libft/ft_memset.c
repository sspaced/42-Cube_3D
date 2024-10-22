/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:34:59 by loic              #+#    #+#             */
/*   Updated: 2024/08/25 19:23:51 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memset(void *p, int value, size_t size)
{
	char	*new_p;

	new_p = p;
	while (size)
	{
		*new_p = (unsigned char)value;
		new_p++;
		size--;
	}
	return (p);
}
