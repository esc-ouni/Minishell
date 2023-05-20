/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:40:47 by idouni            #+#    #+#             */
/*   Updated: 2023/05/20 16:01:32 by idouni           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Minishell.h"

int	ft_mlstsize(t_mlist *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_cmdsize(t_cmd *cmd)
{
	size_t	i;
	t_cmd	*n_cmd;

	i = 0;
	n_cmd = cmd;
	while (n_cmd)
	{
		n_cmd = n_cmd->next;
		i++;
	}
	return (i);
}

t_mlist	*ft_mlstnew(t_collector **collector, char *s)
{
	t_mlist	*new_node;

	new_node = NULL;
	new_node = h_malloc(collector, sizeof(t_mlist), new_node);
	if (new_node)
	{
		new_node->cmd = ft_mstrdup(collector, s);
		new_node->next = NULL;
	}
	return (new_node);
}

t_mlist	*ft_mlstlast(t_mlist *lst)
{
	void	*node;

	if (lst == NULL)
		return (NULL);
	node = lst;
	while (lst != NULL)
	{
		node = lst;
		lst = lst->next;
	}
	return (node);
}

void	ft_mlstadd_back(t_mlist **lst, t_mlist *new)
{
	t_mlist	*o_last;

	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	o_last = ft_mlstlast(*lst);
	o_last->next = new;
	new->next = NULL;
}

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

void	add_lexer(t_collector **collector, t_lexer **head, char *content, t_enum	type)
{
	t_lexer	*tmp;
	t_lexer	*new_node;

	new_node = NULL;
	new_node = h_malloc(collector, sizeof(t_lexer), new_node);
	new_node->cmd = ft_mstrdup(collector, content);
	new_node->type = type;

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

char	**mgetenv(t_collector **collector, char **env)
{
	int		i = 0;
	char	**new_env;

	new_env = NULL;
	while (env[i])
        i++;
	new_env = h_malloc(collector, sizeof(char *) * (i + 1), new_env );
    i = -1;
	while(env[++i])
		new_env[i] = ft_mstrdup(collector, env[i]);
	new_env[i] = NULL;
	return (new_env);
}

char	*minimizer(t_collector **collector, char *s)
{
	char	*ns;
	int		i;

	i = 0;
	ns = NULL;
	ns = h_malloc(collector, ft_strlen(s) + 1, ns);
	while (s[i])
	{
		if (s[i] <= 'Z' && s[i] >= 'A')
			ns[i] = s[i] + 32;
		else
			ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

t_built	cmd_type(t_collector **collector, char *cmd)
{
	if (!ft_strncmp(minimizer(collector, cmd), "echo", ft_strlen("echo")) && (ft_strlen(cmd) == ft_strlen("echo")))
		return(ECH);
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")) && (ft_strlen(cmd) == ft_strlen("cd")))
		return(CD);
	else if (!ft_strncmp(minimizer(collector, cmd), "pwd", ft_strlen("pwd")) && (ft_strlen(cmd) == ft_strlen("pwd")))
		return(PWD);
    else if (!ft_strncmp(cmd, "export", ft_strlen("export")) && (ft_strlen(cmd) == ft_strlen("export")))
		return(EXPT);
    else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")) && (ft_strlen(cmd) == ft_strlen("unset")))
		return(UNST);
    else if (!ft_strncmp(minimizer(collector, cmd), "env", ft_strlen("env")) && (ft_strlen(cmd) == ft_strlen("env")))
		return(ENV);
	else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")) && (ft_strlen(cmd) == ft_strlen("exit")))
		return(EXT);
	else
		return(NOT);
}

void	emplify(t_collector **collector, t_cmd *cmd, char **env)
{
    t_file   *h_file;
    t_cmd *n_cmd;
    char **menv;

	if (!cmd)
		return ;
    menv = mgetenv(collector, env);
    n_cmd = cmd;
	while (n_cmd)
	{
		// n_cmd->num_cmds = ft_mlstsize(cmd);
		n_cmd->myenv = menv;
		if (n_cmd->cmd[0])
			n_cmd->builtflag = cmd_type(collector, n_cmd->cmd[0]);
		h_file = n_cmd->out_files;
		if (h_file)
		{
			while (h_file->next)
			{
				h_file->islast = 0;
				h_file = h_file->next;
			}
			h_file->islast = 1;
		}
		h_file = n_cmd->in_files;
		if (h_file)
		{
			while (h_file->next)
			{
				h_file->islast = 0;
				h_file = h_file->next;
			}
			h_file->islast = 1;
		}
		n_cmd = n_cmd->next;
	}
}

char	*ft_getenv(t_collector **collector, char *key, t_env **menv)
{
	(void)key;
	t_env	*env;

	env = *menv;
	char *key_part;
	key_part = NULL;
	while (env)
	{
		key_part = ft_msplit(collector, env->str, '=')[0];
		if (!ft_strncmp(key, key_part, ft_strlen(key)) && ft_strlen(key) == ft_strlen(key_part))
			return (ft_strchr(env->str, '=') + 1);
		key_part = NULL;
		env = env->next;
	}
	return (NULL);
}
