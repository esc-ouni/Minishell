/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:48:27 by idouni            #+#    #+#             */
/*   Updated: 2023/05/26 13:48:12 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//EWD
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

t_env    *ft_set_env_list(char **env)
{
	t_env   *myenv;
	myenv = NULL;
	int i=0;

	while (env[i])
		env_add_back(&myenv, new_env(env[i++]));
	return (myenv);
}
//EWD

int main(int argc, char **argv, char **env) 
{
    (void)argc;
    (void)argv;
	char		*s;
    t_lexer		*h_lexer;
    t_collector	*collector;
    t_cmd		*cmd;
	t_env		*myenv_list;


	collector = NULL;
	myenv_list = ft_set_env_list(env);
    while (1)
    {
		s = prompt();
        h_lexer = parser(&collector, &myenv_list, s);
        cmd = parser2(&collector, h_lexer);
        emplify(&collector, cmd);
        after_parse2(cmd);
		ft_collectorclear(&collector);
    }
    return 0;
}
