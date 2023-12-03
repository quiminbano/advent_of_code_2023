
#include "utils.h"

void	print_list(t_coord **a)
{
	t_coord	*temp;

	temp = *a;
	while (temp != NULL)
	{
		printf("x1: %zu, x2: %zu, y: %zu, value: %zu ->\n", temp->x1, temp->x2, temp->y, temp->value);
		temp = temp->next;
	}
}

void	free_list(t_coord **lst)
{
	t_coord	*temp;
	t_coord	*temp2;

	if ((*lst) == NULL)
		return ;
	temp2 = (*lst)->next;
	temp = (*lst);
	while (temp->next != NULL)
	{
		free(temp);
		temp = temp2;
		temp2 = temp2->next;
	}
	free(temp);
}


size_t	size_list(t_coord **lst)
{
	size_t		i;
	t_coord	*temp;

	i = 0;
	temp = *lst;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

static t_coord	*new_node(size_t x1, size_t x2, size_t y, size_t value)
{
	t_coord	*new;

	new = (t_coord *)malloc(sizeof(t_coord));
	if (new == NULL)
		return (NULL);
	new->x1 = x1;
	new->x2 = x2;
	new->y = y;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	add_node(t_coord **lst, size_t x1, size_t x2, size_t y, size_t value)
{
	t_coord	*new;
	t_coord	*iter;

	iter = *lst;
	new = new_node(x1, x2, y, value);
	if (!new)
	{
		free_list(lst);
		return (1);
	}
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
	return (0);
}
