/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:17:57 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/06 12:50:09 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_env_node(t_struct *cable, t_envlst *exist)
{
	t_envlst	*envlst;

	envlst = cable->envlst;
	if (cable->envlst == exist)
		cable->envlst = cable->envlst->next;
	else
	{
		while (envlst->next != exist)
			envlst = envlst->next;
		envlst->next = envlst->next->next;
	}
}

int	ft_valid_unset(const char *str)
{
	char	*s;
	s = (char *)str;
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (0);
		s++;
	}
	return (1);
}
void	ft_unset_envlst(t_struct *cable, char *str)
{
	t_envlst	*exist;

	exist = ft_var_env_exist(cable->envlst, str);
	if (exist)
		ft_skip_env_node(cable, exist);
}

void	ft_unset(t_struct *cable, char *str)
{
	if (!ft_valid_unset(str))
		return ;
	ft_unset_envlst(cable, str);
	// ft_unset_explst();
}
