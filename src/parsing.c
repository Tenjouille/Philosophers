/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:31:09 by tbourdea          #+#    #+#             */
/*   Updated: 2023/09/08 14:27:54 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(char *str)
{
	int		i;
	int		res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-')
	{
		i++;
		sign = -sign;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-' )
			return (2147483648);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}