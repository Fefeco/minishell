/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:53:07 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:28:46 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	word = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			count++;
		else if (s[i] == c && count > 0)
		{
			count = 0;
			word++;
		}
		i++;
	}
	if (count > 0)
		word++;
	return (word);
}

static char	**assign_mem(char **array, char const *s, char c)
{
	int	i;
	int	len;
	int	word;

	i = 0;
	len = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			len++;
		if ((s[i] == c && len > 0) || (s[i] != c && s[i + 1] == '\0'))
		{
			array[word] = malloc(sizeof(char) * (len + 1));
			if (!array[word])
				return (NULL);
			len = 0;
			word++;
		}
		i++;
	}
	return (array);
}

static char	**copy_letters(char **array, char const *s, char c)
{
	int	i;
	int	word;
	int	letter;

	i = 0;
	word = 0;
	letter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			array[word][letter++] = s[i];
		if (s[i] != c && s[i + 1] == '\0')
			array[word][letter] = '\0';
		else if (s[i] == c && i > 0 && s[i - 1] != c)
		{
			array[word][letter] = '\0';
			word++;
			letter = 0;
		}
		i++;
	}
	return (array);
}

static char	**free_mem(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	int		wordcount;

	if (!s)
	{
		array = malloc(sizeof(char) * 1);
		if (!array)
			return (NULL);
		*array = NULL;
		return (array);
	}
	wordcount = count_words(s, c);
	array = malloc(sizeof(*array) * (wordcount + 1));
	if (!array)
		return (NULL);
	if (assign_mem(array, s, c))
	{
		copy_letters(array, s, c);
		array[wordcount] = NULL;
	}
	else
		array = free_mem(array);
	return (array);
}

/*
int main(void)
{
	char const s[100] = "  Mi My        name is Simon enfin   	  o";
	//char s[100] = "     ";
	char c = ' ';
	int	i;
	char **result;
	i = 0;
	result = ft_split(s, c);
	while (result[i] != NULL)
	{
		printf("__%s__\n", result[i]);
		i++;
	}
	free_mem(result);
	return (0);
}*/
