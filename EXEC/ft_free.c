/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 21:07:20 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/30 21:08:55 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pos(char **strp, int pos)
{
	while (pos--)
		free(strp[pos]);
	free(strp);
}

void	ft_free_env_lst(t_env **env_lst)
{
	t_env	*tmp;

	while (*env_lst)
	{
		free((*env_lst)->str);
		tmp = *env_lst;
		*env_lst = (*env_lst)->next;
		free(tmp);
	}
}

void	ft_end_free(t_env **env_lst, char **myenv, t_init *init_val)
{
	if (myenv)
		ft_free_stringp(myenv);
	if (*env_lst)
		ft_free_env_lst(env_lst);
	if (init_val->exp_lst)
		ft_free_env_lst(&init_val->exp_lst);
	if (init_val)
		free(init_val);
	rl_clear_history();
	exit(0);
}

void	ft_free_stringp(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i++]);
	}
	free(env);
}
