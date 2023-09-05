/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:04:43 by tbourdea          #+#    #+#             */
/*   Updated: 2022/12/06 13:52:00 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_print_unsigned_long_base(unsigned long long nb, char *base)
{
	unsigned int	b;
	unsigned int	len;

	len = 0;
	b = ft_strlen(base);
	if (nb >= b)
	{
		len += ft_print_unsigned_long_base(nb / b, base);
		len += ft_print_unsigned_long_base(nb % b, base);
	}
	else
		len += ft_printchar(base[nb]);
	return (len);
}

unsigned int	ft_printptr(unsigned long long nb)
{
	unsigned int	len;

	len = 0;
	if (nb == 0)
		len += ft_printstr("(nil)");
	else
	{
		len += ft_printstr("0x");
		len += ft_print_unsigned_long_base(nb, "0123456789abcdef");
	}
	return (len);
}
