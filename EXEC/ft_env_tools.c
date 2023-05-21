/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:19:48 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/21 01:30:46 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_size(t_env *myenv)
{
	size_t	i;

	i = 0;
	while (myenv)
	{
		i++;
		myenv = myenv->next;
	}
	return (i);
}

t_env	*ft_set_env_list(char **env)
{
	t_env	*myenv;
	int		i;

	myenv = NULL;
	i = 0;
	while (env[i])
	{
		env_add_back(&myenv, new_env(env[i]));
		i++;
	}
	return (myenv);
}
