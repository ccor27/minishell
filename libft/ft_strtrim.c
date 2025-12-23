/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:31:48 by crosorio          #+#    #+#             */
/*   Updated: 2025/04/16 16:33:01 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_valid_character(char const *set, char c, int i)
{
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

static void	ft_fill_up_clean_string(const char *s1, char *result, int start,
		int end)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		result[i] = s1[start];
		i++;
		start++;
	}
	result[i] = '\0';
}

static char	*ft_hanlde_null_cases(char const *s1, char const *set,
		char *str_trimmed)
{
	if (!s1)
		return (ft_strdup(""));
	if (!set)
	{
		str_trimmed = malloc((ft_strlen(s1) + 1) * sizeof(char));
		if (!str_trimmed)
			return (NULL);
		return (ft_memcpy(str_trimmed, s1, ft_strlen(s1) + 1));
	}
	return (str_trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_trimmed;
	int		start;
	int		end;

	str_trimmed = NULL;
	if (!s1 && !set)
		return (ft_strdup(""));
	if (!s1 || !set)
		return (ft_hanlde_null_cases(s1, set, str_trimmed));
	else
	{
		start = 0;
		while (!ft_is_valid_character(set, s1[start], 0))
			start++;
		end = ft_strlen(s1) - 1;
		while (!ft_is_valid_character(set, s1[end], 0))
			end--;
		if (start > end)
			return (ft_strdup(""));
		str_trimmed = malloc(((end - start) + 2) * sizeof(char));
		if (!str_trimmed)
			return (NULL);
		ft_fill_up_clean_string(s1, str_trimmed, start, end);
		return (str_trimmed);
	}
}
