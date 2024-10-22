/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:11:50 by loic              #+#    #+#             */
/*   Updated: 2024/09/22 18:51:01 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *str1, const char *str2, size_t size)
{
	while (*str1 == *str2 && size && *str1)
	{
		str1++;
		str2++;
		size--;
	}
	if (size == 0)
	{
		return (0);
	}
	else
	{
		return ((unsigned char)*str1 - (unsigned char)*str2);
	}
}
