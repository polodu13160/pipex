/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:05:33 by pde-petr          #+#    #+#             */
/*   Updated: 2025/02/11 16:42:53 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	check_null_pointer(void *pointer)
{
	if (!pointer)
		return (write(1, "(nil)", 5));
	return (write(1, "0x", 2) + ft_printhexa((unsigned long int)pointer, 'x'));
}

static int	check_null_string(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	return (ft_putstr_fd(str, 1));
}

int	ft_printf_format(char format, va_list arg)
{
	if (format == 'c')
		return (ft_putchar_fd(va_arg(arg, int), 1));
	if (format == 's')
		return (check_null_string(va_arg(arg, char *)));
	if (format == 'i' || format == 'd')
		return (ft_putnbr_fd(va_arg(arg, int), 1));
	if (format == 'x')
		return (ft_printhexa(va_arg(arg, unsigned int), format));
	if (format == 'X')
		return (ft_printhexa(va_arg(arg, unsigned int), format));
	if (format == 'u')
		return (ft_putnbr_fd(va_arg(arg, unsigned int), 1));
	if (format == '%')
		return (write(1, "%", 1));
	if (format == 'p')
		return (check_null_pointer(va_arg(arg, void *)));
	return (write(1, &format, 1));
}
