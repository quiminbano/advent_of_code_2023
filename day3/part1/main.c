#include "utils.h"

static int	iterate_borders(char **map, size_t x1, size_t x2, size_t y)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = x2 + 1;
	if (x1)
		start = x1 - 1;
	if (map[y][end])
		end += 1;
	while (start < end)
	{
		if (isprint(map[y][start]) && !isdigit(map[y][start]) && map[y][start] != '.')
			return (1);
		start++;
	}
	return (0);
}

static size_t	get_sum(t_coord **begin, char **map)
{
	t_coord	*temp;
	size_t	sum;
	size_t	length;

	sum = 0;
	temp = *begin;
	length = size_split(map);
	while (temp)
	{
		if (temp->x1 && isprint(map[temp->y][temp->x1 - 1]) && !isdigit(map[temp->y][temp->x1 - 1]) && map[temp->y][temp->x1 - 1] != '.')
			sum += temp->value;
		else if (map[temp->y][temp->x2 + 1] && isprint(map[temp->y][temp->x2 + 1]) && !isdigit(map[temp->y][temp->x2 + 1]) && map[temp->y][temp->x2 + 1] != '.')
			sum += temp->value;
		else if (temp->y && iterate_borders(map, temp->x1, temp->x2, (temp->y - 1)) == 1)
			sum += temp->value;
		else if (((temp->y + 1) < length) && iterate_borders(map, temp->x1, temp->x2, (temp->y + 1)) == 1)
			sum += temp->value;
		else
			sum += 0;
		temp = temp->next;
	}
	return (sum);
}

static t_coord	*get_list(char **map)
{
	t_coord	*coord;
	t_coord	templ;
	size_t	i;
	size_t	j;
	size_t	flag;
	
	bzero(&templ, sizeof(templ));
	coord = NULL;
	i = 0;
	flag = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (isdigit(map[i][j]) && flag == 0)
			{
				templ.x1 = j;
				templ.y = i;
				if (!isdigit(map[i][j + 1]))
				{
					flag = 2;
					templ.x2 = templ.x1;
				}
				else
					flag = 1;	
			}
			else if (isdigit(map[i][j]) && flag == 1 && !isdigit(map[i][j + 1]))
			{
				templ.x2 = j;
				flag = 2;
			}
			if (flag == 2)
			{
				templ.value = atoi(map[i] + templ.x1);
				if (add_node(&coord, templ.x1, templ.x2, templ.y, templ.value) == 1)
					return (NULL);
				bzero(&templ, sizeof(templ));
				flag = 0;
			}
			j++;
		}
		i++;
	}
	return (coord);
}

static char	*get_document(int fd)
{
	char	buff[READMAX + 1];
	char	*document;
	int		ret;
	size_t	i;

	ret = 1;
	i = 0;
	document = NULL;
	while (ret > 0)
	{
		ret = read(fd, buff, READMAX);
		if (ret == 0)
			return (document);
		else if (ret == -1)
		{
			if (i > 0)
			{
				free(document);
				document = NULL;
			}
			return (NULL);
		}
		buff[ret] = '\0';
		if (i == 0)
			document = strjoin("", buff);
		else
			document = realloc_and_join(document, buff);
		if (!document)
			return (NULL);
		i++;
	}
	return (document);
}

static int	resolve(char *document)
{
	char	**map;
	t_coord	*coord;
	size_t	sum;

	map = split(document, '\n');
	free(document);
	if (!map)
	{
		write(STDERR_FILENO, "Error parsing the map\n", 22);
		exit(EXIT_FAILURE);
	}
	coord = get_list(map);
	if (!coord)
	{
		split_free(map);
		write(STDERR_FILENO, "Error allocating the list of numbers\n", 37);
		exit(EXIT_FAILURE);
	}
	sum = get_sum(&coord, map);
	split_free(map);
	free_list(&coord);
	printf("The result of the sum is %zu\n", sum);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*document;
	int		fd;

	document = NULL;
	if (argc != 2)
	{
		write(STDERR_FILENO, "Invalid ammount of arguments\n", 29);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Error opening the file\n", 23);
		exit(EXIT_FAILURE);
	}
	document = get_document(fd);
	close(fd);
	if (!document)
	{
		write(STDERR_FILENO, "Error reading the file\n", 23);
		exit(EXIT_FAILURE);
	}
	return (resolve(document));
}