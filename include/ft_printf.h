/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbourdea <tbourdea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:40:39 by tbourdea          #+#    #+#             */
/*   Updated: 2022/12/06 14:10:04 by tbourdea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

unsigned int	ft_printchar(char c);
unsigned int	ft_printstr(const char *str);
unsigned int	t_select(va_list params, char c);
unsigned int	ft_printf(const char *str, ...);
unsigned int	ft_printnbr_base(int nbr, char *base);
unsigned int	ft_size(unsigned int nb, unsigned int b);
unsigned int	ft_strlen(char	*str);
unsigned int	ft_printptr(unsigned long long nb);
unsigned int	ft_printunbr_base(unsigned int nb, char *base);
unsigned int	ft_print_unsigned_long_base(unsigned long long nb, char *base);

#endif