/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:01:54 by crosorio          #+#    #+#             */
/*   Updated: 2025/05/22 16:50:44 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function to get the number of digits in the integer for a given base
static int	ft_know_num_digits(unsigned long n, int base)
{
	int	count;

	count = 1;
	while (n >= (unsigned long)base)
	{
		n /= base;
		count++;
	}
	return (count);
}

// Function to convert integer to string for a given base
static char	*ft_convert_int_to_string(unsigned long n, int size, char *s,
		int base)
{
	const char	base_digits[] = "0123456789ABCDEF";

	s[size] = '\0';
	while (size--)
	{
		s[size] = base_digits[n % base];
		n /= base;
	}
	return (s);
}

// Main function to convert integer to string based on a given base
char	*ft_itoa_base(unsigned long n, int base)
{
	char	*num_in_string;
	int		num_of_digits;

	if (base < 2 || base > 16)
		return (NULL);
	num_of_digits = ft_know_num_digits(n, base);
	num_in_string = malloc((num_of_digits + 1) * sizeof(char));
	if (!num_in_string)
		return (NULL);
	return (ft_convert_int_to_string(n, num_of_digits, num_in_string, base));
}
/*if (n >= (unsigned long) base)
	return (ft_know_num_digits(n / base, num + 1, base));
return (num);*/
