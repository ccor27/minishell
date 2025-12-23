/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:04:28 by crosorio          #+#    #+#             */
/*   Updated: 2025/05/21 16:24:43 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Funtion to handle the case of
 * percentage character
 */
int	ft_handle_percentage(void)
{
	char	*value;

	value = ft_strdup("%");
	if (!value)
		return (0);
	ft_putchar_fd('%', 1);
	free(value);
	return (1);
}

/**
 * Function to handle the case of string
 */
int	ft_handle_string(char *string)
{
	int	count;

	if (!string)
		return (ft_putstr_fd("(null)", 1));
	count = 0;
	count += ft_putstr_fd(string, 1);
	return (count);
}

/**
 * Function to handle the case of character
 */
int	ft_handle_character(char c)
{
	if (!ft_isprint(c))
		return (0);
	ft_putchar_fd(c, 1);
	return (1);
}
