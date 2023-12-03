#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <stdio.h>
# include <fcntl.h>
# include <ctype.h>

# define READMAX 4096

typedef struct s_coord
{
	size_t			value;
	struct s_coord	*next;

}	t_coord;

char	*realloc_and_join(char *s1, char const *s2);
char	**split(char const *s, char c);
char	**split_free(char **array);
size_t	size_split(char **arr);
char	*strjoin(char const *s1, char const *s2);
int		add_node(t_coord **lst, size_t value);
void	free_list(t_coord **lst);
size_t	size_list(t_coord **lst);
void	print_list(t_coord **a);

#endif