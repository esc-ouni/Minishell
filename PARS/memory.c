
#include "minishell.h"

void	*h_malloc(t_collector **collector_head, size_t s, void *p)
{
	t_collector *tmp;
    t_collector *new_node;
	new_node = malloc(sizeof(t_collector));
	p = malloc(s);
	if (!new_node || !p)
	{
		printf("MALLOC\n");
		ft_collectorclear(collector_head);
		exit (1);
	}
	new_node->addr = p;
    if (!(*collector_head))
    {
        *collector_head = new_node;
        new_node->next = NULL;
    }
    else
    {
        tmp = *collector_head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        new_node->next = NULL;
    }
	return (p);
}

void	ft_collectorclear(t_collector **collector)
{
	t_collector	*node;
	t_collector	*n_node;

	if (!collector)
		return ;
	node = *collector;
	while (node)
	{
		// printf("%p\n", node->addr);
		n_node = node->next;
		free(node->addr);
		free(node);
		node = n_node;
	}
	*collector = NULL;
}

void	debug(void)
{
	printf("\x1B[32m");
	printf("\nDEBUG OK\n");
	printf("\x1B[0m");
}