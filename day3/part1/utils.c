#include "utils.h"

size_t	size_split(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

char	*realloc_and_join(char *s1, char const *s2)
{
	size_t		a;
	size_t		b;
	size_t		i;
	char		*dest;

	a = strlen(s1);
	b = strlen(s2);
	i = 0;
	dest = (char *)malloc(sizeof(char) * ((a + b) + 1));
	if (dest == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (i < (a + b))
	{
		if (i < a)
			dest[i] = s1[i];
		else
			dest[i] = s2[i - a];
		i++;
	}
	dest[i] = '\0';
	free(s1);
	s1 = NULL;
	return (dest);
}