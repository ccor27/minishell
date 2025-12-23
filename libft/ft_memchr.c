/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:23:56 by crosorio          #+#    #+#             */
/*   Updated: 2025/04/15 15:31:24 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_copy;

	i = 0;
	s_copy = (unsigned char *)s;
	while (i < n)
	{
		if (s_copy[i] == (unsigned char)c)
			return ((void *)&s_copy[i]);
		i++;
	}
	return (0);
}
