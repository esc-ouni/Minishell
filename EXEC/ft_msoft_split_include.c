/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msoft_split_include.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:46:50 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/05 17:52:09 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **ft_msoft_split_include(char *str, char c, t_struct *cable)
{
    char    **res;
    char    **tmp;
    int trimlen;

    res = h_malloc(cable->collector, sizeof(char *) * 3, res, TMP);
    tmp = res;
    trimlen = ft_trim_len(str, c);
    *res = h_malloc(cable->collector, trimlen + 2, *res, TMP);
    ft_strlcpy(*(res++), str, trimlen + 2);
    *res = ft_msubstr(cable, str, trimlen + 1, ft_strlen(str) - trimlen - 1);
    *res = NULL;
    return (tmp);
}
