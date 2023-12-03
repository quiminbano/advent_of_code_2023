
#include "utils.h"

void	print_list(t_coord **a)
{
	t_coord	*temp;

	temp = *a;
	while (temp != NULL)
	{
		printf("value: %zu ->", temp->value);
		temp = temp->next;
	}
	printf("\n");
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

static t_coord	*new_node(size_t value)
{
	t_coord	*new;

	new = (t_coord *)malloc(sizeof(t_coord));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

int	add_node(t_coord **lst, size_t value)
{
	t_coord	*new;
	t_coord	*iter;

	iter = *lst;
	new = new_node(value);
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
