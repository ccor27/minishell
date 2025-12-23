/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:14:35 by crosorio          #+#    #+#             */
/*   Updated: 2025/05/13 17:14:52 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_know_num_digits_unsigned(unsigned int n, int num)
{
	if (n > 0)
		return (ft_know_num_digits_unsigned(n / 10, num + 1));
	return (num);
}

static char	*ft_convert_unsigned_to_string(unsigned int n, int size, char *s)
{
	int	total_size;

	total_size = size;
	s[total_size] = '\0';
	while (total_size--)
	{
		s[total_size] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}

char	*ft_utoa(unsigned int n)
{
	char	*num_in_string;
	int		num_of_digits;

	if (n == 0)
		return (ft_strdup("0"));
	num_of_digits = ft_know_num_digits_unsigned(n, 0);
	num_in_string = malloc((num_of_digits + 1) * sizeof(char));
	if (!num_in_string)
		return (NULL);
	return (ft_convert_unsigned_to_string(n, num_of_digits, num_in_string));
}
