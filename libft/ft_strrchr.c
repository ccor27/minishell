/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:36:46 by crosorio          #+#    #+#             */
/*   Updated: 2025/04/16 12:46:39 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_lenght;

	s_lenght = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)&s[s_lenght]);
	while (s_lenght--)
	{
		if (s[s_lenght] == (unsigned char)c)
			return ((char *)&s[s_lenght]);
	}
	return (0);
}
