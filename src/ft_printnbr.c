/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:05:37 by tbourdea          #+#    #+#             */
/*   Updated: 2022/12/06 13:51:40 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_strlen(char	*str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned int	ft_printnbr_base(int nbr, char *base)
{
	unsigned int	b;
	unsigned int	len;
	long			nb;

	len = 0;
	nb = nbr;
	b = ft_strlen(base);
	if (nb < 0)
	{
		nb = -nb;
		len += ft_printchar('-');
	}
	if (nb >= b)
	{
		len += ft_printnbr_base(nb / b, base);
		len += ft_printnbr_base(nb % b, base);
	}
	else
		len += ft_printchar(base[nb]);
	return (len);
}

unsigned int	ft_printunbr_base(unsigned int nb, char *base)
{
	unsigned int	b;
	unsigned int	len;

	len = 0;
	b = ft_strlen(base);
	if (nb >= b)
	{
		len += ft_printunbr_base(nb / b, base);
		len += ft_printunbr_base(nb % b, base);
	}
	else
		len += ft_printchar(base[nb]);
	return (len);
}
