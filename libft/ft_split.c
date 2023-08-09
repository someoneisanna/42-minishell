/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:57:28 by ataboada          #+#    #+#             */
/*   Updated: 2023/06/30 10:52:20 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ft_strcount(char const *str, char c);
int ft_wordlen(char const *str, char c, int b);
char *ft_addword(char const *str, char c, int b);
char **ft_split(char const *str, char c);

int main(void)
{
	int i;
	char **split;

	split = ft_split("how are   youdoing   there mate  ", ' ');

	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}
*/

int	ft_strcount(char const *str, char c)
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

int	ft_wordlen(char const *str, char c, int b)
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

char	*ft_addword(char const *str, char c, int b)
{
	int		i;
	int		j;
	int		len;
	char	*word;

	i = b;
	j = 0;
	len = ft_wordlen(str, c, b);
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

char	**ft_split(char const *str, char c)
{
	int		i;
	int		j;
	char	**strs;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (ft_strcount(str, c) + 1));
	if (!strs)
		return (NULL);
	while (*(str + i))
	{
		while (*(str + i) && *(str + i) == c)
			i++;
		if (*(str + i))
			strs[j++] = ft_addword(str, c, i++);
		while (*(str + i) && *(str + i) != c)
			i++;
	}
	strs[j] = NULL;
	return (strs);
}
