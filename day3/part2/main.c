#include "utils.h"

size_t	product_list(t_coord **coord)
{
	size_t	size;
	size_t	product;
	t_coord	*temp;

	temp = *coord;
	product = 1;
	size = size_list(&temp);
	if (size == 1)
		return (0);
	while (temp)
	{
		product *= temp->value;
		temp = temp->next;
	}
	return (product);
}

static int	find_numbers(char **map, size_t x, size_t y, t_coord **coord)
{
	size_t	left;
	size_t	right;
	char	*templ;
	char	**numbers;
	size_t	i;

	left = x;
	right = x;
	i = 0;
	templ = NULL;
	while (left && isdigit(map[y][left - 1]))
		left--;
	while (isdigit(map[y][right + 1]))
		right++;
	right++;
	if ((left + 1) == right)
		return (0);
	templ = (char *)malloc(sizeof(char) * ((right - left) + 1));
	if (!templ)
	{
		free_list(coord);
		return (1);
	}
	strlcpy(templ, (map[y] + left), ((right - left) + 1));
	if (!isdigit(map[y][x]))
		numbers = split(templ, map[y][x]);
	else
		numbers = split(templ, '.');
	if (!numbers)
	{
		free_list(coord);
		free(numbers);
		return (1);
	}
	free(templ);
	templ = NULL;
	while (numbers[i])
	{
		if (isdigit(numbers[i][0] && add_node(&(*coord), (size_t)atoi(numbers[i]))))
		{
			split_free(numbers);
			free_list(coord);
			return (1);
		}
		i++;
	}
	split_free(numbers);
	return (0);
}

static int	fill_list(char **map, size_t j, size_t i, t_coord **coord)
{
	if ((j && isdigit(map[i][j - 1])) || (map[i][j + 1] && isdigit(map[i][j + 1])))
	{
		if (find_numbers(map, j, i, &(*coord)) == 1)
			return (1);
	}
	if (i)
	{
		if (find_numbers(map, j, (i - 1), &(*coord)) == 1)
			return (1);
	}
	if ((i + 1) < size_split(map))
	{
		if (find_numbers(map, j, (i + 1), &(*coord)) == 1)
			return (1);
	}
	return (0);
}

static int	get_sum(char **map, size_t *sum)
{
	t_coord	*lst;
	size_t	i;
	size_t	j;

	i = 0;
	lst = NULL;
	(*sum) = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '*' && fill_list(map, j, i, &lst))
				return (1);
			if (size_list(&lst) > 0)
				(*sum) += product_list(&lst);
			free_list(&lst);
			lst = NULL;
			j++;
		}
		i++;
	}
	return (0);
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
	size_t	sum;
	int		flag;

	map = split(document, '\n');
	free(document);
	if (!map)
	{
		write(STDERR_FILENO, "Error parsing the map\n", 22);
		exit(EXIT_FAILURE);
	}
	flag = get_sum(map, &sum);
	if (flag == 1)
	{
		split_free(map);
		write(STDERR_FILENO, "Error processing the data\n", 26);
		exit(EXIT_FAILURE);
	}
	split_free(map);
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