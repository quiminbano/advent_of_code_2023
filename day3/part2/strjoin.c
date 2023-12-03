#include "utils.h"

char	*strjoin(char const *s1, char const *s2)
{
	size_t	a;
	size_t	b;
	size_t	i;
	char	*dest;

	a = strlen(s1);
	b = strlen(s2);
	i = 0;
	dest = (char *)malloc(sizeof(char) * ((a + b) + 1));
	if (dest == NULL)
		return (NULL);
	while (i < (a + b))
	{
		if (i < a)
			dest[i] = s1[i];
		else
			dest[i] = s2[i - a];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
