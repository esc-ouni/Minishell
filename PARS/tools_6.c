#include "minishell.h"

void 	add_to_cmd(t_collector **collector, t_cmd **head, char **full_cmd, t_file *out_files, t_file *in_files)
{
	int		i = 0;
	t_file	*out_files2;
	t_file	*in_files2;
	char **str;
	str = NULL;
	t_cmd	*tmp;

	t_cmd *new_cmd = NULL;
	new_cmd = h_malloc(collector, sizeof(t_cmd), new_cmd);

	out_files2 = NULL;
	in_files2 = NULL;

	if (full_cmd)
	{
		while (full_cmd[i])
			i++;
		str = h_malloc(collector, sizeof(char *) * (i + 1), str);
	}
	else
	{
		str = h_malloc(collector, sizeof(char *), str);
		str[0] = NULL;
	}
	i = 0;
	if (full_cmd)
	{
		while (full_cmd[i])
		{
			str[i] = ft_mstrdup(collector, full_cmd[i]);
			i++;
		}
		str[i] = NULL;
	}
	else
		str[i] = NULL;

	while (out_files)
	{
		add_file_file(collector, &out_files2, out_files);
		out_files = out_files->next;
	}

	while (in_files)
	{
		add_file_file(collector, &in_files2, in_files);
		in_files = in_files->next;
	}

	new_cmd->cmd = str;
	new_cmd->out_files = out_files2;
	new_cmd->in_files = in_files2;

	if (!(*head))
    {
        *head = new_cmd;
        new_cmd->next = NULL;
    }
    else
    {
        tmp = *head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_cmd;
        new_cmd->next = NULL;
    }
}
