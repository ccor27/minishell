/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:01:54 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/15 12:24:06 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (num * sign);
}

static int	skip_whitespace_and_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_atoi_safe(const char *nptr, int *out)
{
	int		i;
	int		sign;
	long	num;

	i = skip_whitespace_and_sign(nptr, &sign);
	num = 0;
	if (!ft_isdigit(nptr[i]))
		return (0);
	while (ft_isdigit(nptr[i]))
	{
		num = num * 10 + (nptr[i] - '0');
		if (sign == 1 && num > INT_MAX)
			return (0);
		if (sign == -1 && - num < INT_MIN)
			return (0);
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	*out = (int)(sign * num);
	return (1);
}
