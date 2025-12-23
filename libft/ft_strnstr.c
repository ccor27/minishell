/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:41:44 by crosorio          #+#    #+#             */
/*   Updated: 2025/04/15 10:14:36 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;
	size_t	j;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (len - i < little_len)
			break ;
		j = 0;
		while (j < little_len && (i + j) < len && big[i + j] == little[j])
			j++;
		if (j == little_len)
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
