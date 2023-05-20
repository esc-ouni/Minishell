#include "Minishell.h"

void	ft_mlstclear(t_mlist **lst)
{
	t_mlist	*node;
	t_mlist	*n_node;

	if (!lst)
		return ;
	node = *lst;
	while (node)
	{
		n_node = node->next;
		free(node->cmd);
		free(node);
		node = n_node;
	}
	*lst = NULL;
}     

void	add_file_node(t_collector	**collector, t_file **head, char *filename, int flag)
{
    t_file *tmp;
    t_file *new_node = NULL;
    new_node = h_malloc(collector, sizeof(t_file), new_node);
    
    new_node->filename = ft_mstrdup(collector, filename);
    new_node->o_flags = flag;
    
    if (!(*head))
    {
        *head = new_node;
        new_node->next = NULL;
    }
    else
    {
        tmp = *head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        new_node->next = NULL;
    }
}

void	add_file_file(t_collector **collector, t_file **head, t_file *file)
{
    t_file *tmp;
    t_file *new_node = NULL;
    new_node = h_malloc(collector, sizeof(t_file), new_node);
    
    new_node->filename = ft_mstrdup(collector, file->filename);
    new_node->o_flags = file->o_flags;
    
    if (!(*head))
    {
        *head = new_node;
        new_node->next = NULL;
    }
    else
    {
        tmp = *head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        new_node->next = NULL;
    }
}

void	add_to_fullcmd(t_collector	**collector, char ***full_cmd, t_lexer *n, int j)
{
	int	l;
    t_lexer *tmp;

	l = 0;
    if (!((*full_cmd)))
    {
		tmp = n;
		while(tmp && tmp->type != PIP)
		{
			l++;
			tmp = tmp->next;
		}
		(*full_cmd) = h_malloc(collector, sizeof(char *) * (l + 1), *full_cmd);
		(*full_cmd)[0] = ft_mstrdup(collector, n->cmd);
		(*full_cmd)[1] = NULL;
		return ;
    }    
    else
    {
        while ((*full_cmd)[l])
            l++;
		if (j && l)
		{
			l--;
			(*full_cmd)[l] = ft_mstrjoin(collector, (*full_cmd)[l], n->cmd);
			(*full_cmd)[l+1] = NULL;
			return ;			
		}
		else
		{
			(*full_cmd)[l] = ft_mstrdup(collector, n->cmd);
			(*full_cmd)[l+1] = NULL;
			return ;
		}
    }
}
