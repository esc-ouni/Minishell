#include "minishell.h"

static t_env   *new_env(char   *str)
{
    t_env   *lst;

    lst = malloc(sizeof(t_env));
    lst->str = str;
    lst->next = NULL;
    return(lst);
}

static void   env_add_back(t_env **env, t_env *toadd)
{
    t_env *head;

    head = *env;
    if (!(*env))
    {
        *env = new_env(toadd->str);
        head = *env;
        return ;
    }
    while ((*env)->next)
        (*env) = (*env)->next;
    (*env)->next = toadd;
    *env = head;
}

size_t  env_size(t_env *myenv)
{
    size_t i;

    i = 0;
    while (myenv)
    {
        i++;
        myenv = myenv->next;
    }
    return (i);
}

t_env    *ft_set_env_list(char **env)
{
    t_env   *myenv;
    myenv = NULL;
    int i=0;

    while (env[i])
        env_add_back(&myenv, new_env(env[i++]));
    return (myenv);
}


void    ft_free_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
        free(env[i++]);
    free(env);
}

char    **ft_set_env(t_env *env_lst, char **myenv)
{
    char    **res;
    int     i;

    i = 0;
    res = (char **)malloc(sizeof(char *) * (env_size(env_lst) + 1));
    while (env_lst)
    {
        res[i] = env_lst->str;
        env_lst = env_lst->next;
        i++;
    }
    res[i] = NULL;
    return (res);
}

char    **ft_make_double_char(t_env *env_lst)
{
    int i;
    char    **res;

    i = env_size(env_lst);
    res = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (env_lst)
    {
        res[i] = ft_strdup(env_lst->str);
        i++;
        env_lst = env_lst->next;
    }
    res[i] = NULL;
    return (res);
}

int ft_is_exported(char *str)
{
    if (str && ft_isalpha(str[0]) && ft_strchr(str, '='))
        return (1);
    return (0);
}

t_env   *ft_var_exist(t_env *env_lst, char *str)
{
    char    **var;

    var = ft_split(str, '=');
    while (env_lst)
    {
        if (!ft_strncmp(env_lst->str, var[0], ft_strlen(var[0])))
            return (env_lst);
        env_lst = env_lst->next;
    }
    ft_free_env(var);
    return (NULL);
}

int ft_edit_env_str(t_env *to_edit, char *str)
{
    free(to_edit->str);
    to_edit->str = ft_strdup(str);
}

char    **ft_export(t_env **env_lst, char *str, char **myenv)
{
    char **res;
    char    *ev_var;

    if (!ft_is_exported(str))
        return (myenv);
    ev_var = ft_var_exist(*env_lst, str);

    if(ev_var)
        ft_edit_env_str(ev_var, str);
    else
        env_add_back(env_lst, new_env(str));
    res = ft_make_double_char(*env_lst);
    return (res);
}


int    ft_unset_lst(t_env **env_lst, char *str)
{
    t_env    *tmp;
    t_env    *tmp2;

    tmp = NULL;
    tmp2 = NULL;
    if (!str)
        return 0;
    while (*env_lst)
    {
        if ((*env_lst)->next && !strncmp((*env_lst)->next->str, str, ft_strlen(str)))
        {
            tmp = (*env_lst)->next;
            if ((*env_lst)->next->next)
                tmp2 = (*env_lst)->next->next;
            (*env_lst)->next = tmp2;
            free(tmp);
            return (1) ;
        }
        *env_lst = (*env_lst)->next;
    }
    return (0);
}

char    **ft_unset(t_env **env_lst, char *str, char **myenv)
{
    t_env   *head;

    head = *env_lst;
    if (!ft_unset_lst(env_lst, str))
        return (myenv);
    *env_lst = head;
    return (ft_set_env(*env_lst, myenv));
}
