/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:53:25 by crosorio          #+#    #+#             */
/*   Updated: 2025/04/15 11:01:22 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	dest_lenght;
	size_t	source_lenght;
	size_t	i;

	i = 0;
	dest_lenght = ft_strlen(dst);
	source_lenght = ft_strlen(src);
	if (size <= 0)
		return (source_lenght);
	if (size <= dest_lenght)
		return (size + source_lenght);
	while ((src[i]) && (dest_lenght + i) < (size - 1))
	{
		dst[dest_lenght + i] = src[i];
		i++;
	}
	dst[dest_lenght + i] = '\0';
	return (dest_lenght + source_lenght);
}
