/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:14:30 by lben-adi          #+#    #+#             */
/*   Updated: 2024/08/25 19:20:26 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_isalnum(int c)
{
	if ((c <= 57 && c >= 48) || ((c <= 90 && c >= 65) || (c <= 122 && c >= 97)))
	{
		return (8);
	}
	return (0);
}
