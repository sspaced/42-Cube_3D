/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:08:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/18 15:09:49 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_part(char element)
{
	if (element == '1' || element == '0' || element == 'N' || element == 'S'
		|| element == 'W' || element == 'E' || element == ' '
		|| element == '\n')
		return (1);
	return (0);
}

int	contain_map_part(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_map_part(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	err_msg(char *info, int line)
{
	ft_putstr_fd("Err with [", 2);
	ft_putstr_fd(info, 2);
	ft_putstr_fd("] at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd("\n", 2);
}
