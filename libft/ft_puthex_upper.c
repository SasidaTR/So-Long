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

int	ft_puthex_upper(unsigned int n)
{
	char	*hex;
	int		len;

	hex = "0123456789ABCDEF";
	len = 0;
	if (n >= 16)
		len += ft_puthex_upper(n / 16);
	len += ft_putchar(hex[n % 16]);
	return (len);
}
