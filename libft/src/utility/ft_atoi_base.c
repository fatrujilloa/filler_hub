/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 10:16:55 by auguyon           #+#    #+#             */
/*   Updated: 2019/01/21 10:27:08 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

static int	ft_base(int nb, int base)
{
	char	base1[17] = "0123456789abcdef";
	char	base2[17] = "0123456789ABCDEF";
	int		i;

	i = 0;
	while (i < base)
	{
		if (nb == base1[i] || nb == base2[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *str, int base)
{
	int	nb;
	int	neg;
	int	i;

	nb = 0;
	neg = 0;
	i = 0;
	while (((str[i] >= 8 && str[i] <= 13) || str[i] == ' ') && str[i])
		i++;
	if (str[i] == '-')
		neg++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && (str[i] >= 'a' && str[i] <= 'f')
				&& (str[i] >= 'A' && str[i] <= 'F'))
	{
		nb = nb * base + (ft_base(str[i], base));
		i++;
	}
	return (neg ? -nb : nb);
}
