/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 23:44:24 by pauldepetri       #+#    #+#             */
/*   Updated: 2024/12/12 03:04:57 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(long int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		return (ft_putstr_fd("-2147483648", fd));
	}
	else
	{
		if (n < 0)
		{
			count += ft_putchar_fd(45, fd);
			n = -n;
		}
		if (n >= 10)
			count += ft_putnbr_fd(n / 10, fd);
		count += (ft_putchar_fd(n % 10 + 48, fd));
	}
	return (count);
}
