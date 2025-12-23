/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:23:59 by crosorio          #+#    #+#             */
/*   Updated: 2025/04/16 12:36:38 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	size_t			i;
	void			*generic_array;
	unsigned char	*unsigned_array;

	total_size = 0;
	if (nmemb == 0 || size == 0)
		total_size = 0;
	else if (nmemb > SIZE_MAX / size)
		return (NULL);
	else
		total_size = nmemb * size;
	generic_array = (int *)malloc(total_size);
	if (generic_array == 0)
		return (NULL);
	unsigned_array = (unsigned char *)generic_array;
	i = 0;
	while (i < total_size)
	{
		unsigned_array[i] = 0;
		i++;
	}
	return (generic_array);
}
