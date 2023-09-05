/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printletters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:20:53 by tbourdea          #+#    #+#             */
/*   Updated: 2022/12/06 12:56:43 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_printchar(char c)
{
	unsigned int	len;

	len = 1;
	write(1, &c, 1);
	return (len);
}

unsigned int	ft_printstr(const char *str)
{
	unsigned int	len;

	len = 0;
	if (!str)
	{
		len += ft_printstr("(null)");
		return (len);
	}
	while (str[len])
		len += ft_printchar(str[len]);
	return (len);
}
