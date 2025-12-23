/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:35:01 by crosorio          #+#    #+#             */
/*   Updated: 2025/04/15 14:37:04 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (n == 0 || dest == src)
		return (dest);
	if ((src + n <= dest) || (dest + n <= src))
		return (ft_memcpy(dest, src, n));
	else
	{
		if (d > s)
		{
			while (n--)
				d[n] = s[n];
		}
		else
		{
			while (n--)
				*d++ = *s++;
		}
	}
	return (dest);
}
