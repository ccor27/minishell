/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:13:50 by crosorio          #+#    #+#             */
/*   Updated: 2025/04/16 16:32:05 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_alloc_str(size_t len)
{
	return ((char *)malloc(len * sizeof(char)));
}

static char	*ft_join_strings(char const *s1, char const *s2, size_t i, size_t j)
{
	size_t	s1_length;
	size_t	s2_length;
	char	*new_string;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	new_string = ft_alloc_str(s1_length + s2_length + 1);
	if (!new_string)
		return (NULL);
	while (i < s1_length + s2_length)
	{
		if (i < s1_length)
			new_string[i] = s1[i];
		else
		{
			new_string[i] = s2[j];
			j++;
		}
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s2_copy;
	char	*s1_copy;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
	{
		s2_copy = ft_alloc_str(ft_strlen(s2) + 1);
		if (!s2_copy)
			return (NULL);
		return (ft_memcpy(s2_copy, s2, ft_strlen(s2) + 1));
	}
	else if (!s2)
	{
		s1_copy = ft_alloc_str(ft_strlen(s1) + 1);
		if (!s1_copy)
			return (NULL);
		return (ft_memcpy(s1_copy, s1, ft_strlen(s1) + 1));
	}
	else
		return (ft_join_strings(s1, s2, 0, 0));
}
