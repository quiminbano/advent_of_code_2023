#include "utils.h"

static size_t	count_char(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] == c && c != 0)
		i++;
	return (i);
}

static size_t	strlen_char(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static size_t	wordcount(char const *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

char	**split_free(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}

char	**split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	temp;
	size_t	character;
	size_t	store;

	i = wordcount(s, c);
	store = count_char(s, c);
	array = (char **)malloc(sizeof(char *) * (i + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < wordcount(s, c))
	{
		temp = strlen_char((s + store), c);
		character = count_char((s + store + temp), c);
		array[i] = (char *)malloc(sizeof(char) * (temp + 1));
		if (array[i] == NULL)
			return (split_free(array));
		strlcpy(array[i], (s + store), (temp + 1));
		store = store + (temp + character);
		i++;
	}
	array[i] = NULL;
	return (array);
}
