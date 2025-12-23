/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristian <cristian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:01:54 by crosorio          #+#    #+#             */
/*   Updated: 2025/04/17 10:26:34 by cristian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_know_num_digits(int n, int num)
{
	if (n > 0)
		return (ft_know_num_digits(n / 10, num + 1));
	return (num);
}

static char	*ft_handle_special_cases(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	else
		return (ft_strdup("-2147483648"));
}

static char	*ft_convert_int_to_string(int n, int is_negative, int size, char *s)
{
	int	total_size;

	total_size = size + is_negative;
	s[total_size] = '\0';
	while (total_size--)
	{
		s[total_size] = (n % 10) + '0';
		n /= 10;
	}
	if (is_negative)
		s[0] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	int		is_negative;
	char	*num_in_string;
	int		num_of_digits;

	is_negative = 0;
	if (n == 0 || n <= -2147483648)
		return (ft_handle_special_cases(n));
	if (n < 0)
	{
		is_negative = 1;
		n = n * -1;
	}
	num_of_digits = ft_know_num_digits(n, 0);
	if (is_negative)
		num_in_string = malloc((num_of_digits + 2) * sizeof(char));
	else
		num_in_string = malloc((num_of_digits + 1) * sizeof(char));
	if (!num_in_string)
		return (NULL);
	return (ft_convert_int_to_string(n, is_negative, num_of_digits,
			num_in_string));
}
