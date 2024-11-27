/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:50:54 by loic              #+#    #+#             */
/*   Updated: 2024/09/06 00:02:51 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	character;

	if (n < 0)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			n *= -1;
			write(fd, "-", 1);
		}
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		character = n % 10 + '0';
		write(fd, &character, 1);
	}
	if (n <= 9 && n >= 0)
	{
		character = n % 10 + '0';
		write(fd, &character, 1);
	}
}
