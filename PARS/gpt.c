#include <stdlib.h> // for malloc()
#include <string.h> // for strdup()

typedef struct s_file
{
    char            *filename;
    struct s_file   *next;
} t_file;

void add_file_node(t_file **head, char *filename)
{
    t_file *tmp;
    t_file *new_node = malloc(sizeof(t_file));
    
    new_node->filename = strdup(filename);
    
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



