/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-15 14:54:05 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-15 14:54:05 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int		count;
	int		in_word;
	char	quote;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (in_word == 0 && *s != c)
		{
			in_word = 1;
			count++;
		}
		else if (in_word == 1 && *s == c)
			in_word = 0;
		if (*s == '\'' || *s == '"')
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
		}
		s++;
	}
	return (count);
}

static int	ft_get_word_len(const char *s, char c)
{
	int	len;
	int	quote;

	len = 0;
	quote = 0;
	while (s[len])
	{
		if (s[len] == '\'' || s[len] == '"')
		{
			if (quote == 0)
				quote = s[len];
			else if (quote == s[len])
				quote = 0;
		}
		else if (s[len] == c && quote == 0)
			break ;
		len++;
	}
	return (len);
}

static char	*ft_strdup_word(const char *s, int len)
{
	char	*word;
	int		i;
	int		j;
	int		start;

	start = 0;
	if (s[0] == '\'' || s[0] == '"')
	{
		start = 1;
		len -= 2;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = start;
	j = 0;
	while (j < len)
	{
		word[j] = s[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

static void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	**ft_split_quote(const char *s, char c, int i, int j)
{
	char	**matrix;
	int		word_count;
	int		len;

	word_count = ft_count_words(s, c);
	matrix = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] == c)
			i++;
		len = ft_get_word_len(s + i, c);
		matrix[j] = ft_strdup_word(s + i, len);
		if (!matrix[j++])
		{
			ft_free_matrix(matrix);
			return (NULL);
		}
		i = i + len;
	}
	return ((matrix[j] = NULL), matrix);
}
