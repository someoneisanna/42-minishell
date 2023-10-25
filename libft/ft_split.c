/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:57:28 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:37:10 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcount(char const *str, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (*(str + i))
	{
		while (*(str + i) && *(str + i) == c)
		{
			i++;
		}
		if (*(str + i))
		{
			w++;
			i++;
		}
		while (*(str + i) && *(str + i) != c)
		{
			i++;
		}
	}
	return (w);
}

static int	ft_strclen(char const *str, char c, int b)
{
	int	i;
	int	len;

	i = b;
	len = 0;
	while (*(str + i) && (*(str + i) != c))
	{
		len++;
		i++;
	}
	return (len);
}

static char	*ft_addword(char const *str, char c, int b)
{
	int		i;
	int		j;
	int		len;
	char	*word;

	i = b;
	j = 0;
	len = ft_strclen(str, c, b);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (*(str + i) && *(str + i) != c)
	{
		word[j] = *(str + i);
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

/**
 * @brief Allocates (with malloc(3)) and returns an array of strings obtained by
 * splitting the string ’s’ using the character ’c’ as a delimiter. The array
 * will have a NULL pointer at the end.
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings resulting from the split. NULL if the memory
 * allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**strs;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (ft_strcount(s, c) + 1));
	if (!strs)
		return (NULL);
	while (*(s + i))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		if (*(s + i))
			strs[j++] = ft_addword(s, c, i++);
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	strs[j] = NULL;
	return (strs);
}
