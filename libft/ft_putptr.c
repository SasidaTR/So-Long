/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:23:17 by trischma          #+#    #+#             */
/*   Updated: 2024/05/21 14:23:19 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_putptr(void *ptr)
{
	unsigned long	addr;
	int				len;

	if (ptr == NULL)
	{
		ft_putstr("(nil)");
		return (5);
	}
	addr = (unsigned long)ptr;
	len = 2;
	ft_putstr("0x");
	len += ft_puthex(addr);
	return (len);
}
