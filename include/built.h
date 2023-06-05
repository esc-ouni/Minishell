#ifndef BUILT_H
# define BUILT_H

#include "minishell.h"

void	ft_set_env_lst(t_struct *cable, char **ev);
void	ft_env_set(t_struct *cable);
t_envlst	*ft_env_new_node(char *str);
t_envlst	*ft_last_envlst(t_envlst *envlst);
void	ft_env_add_back(t_envlst **envlst, t_envlst *toadd);
t_exp	*ft_exp_new_node(char *str);
t_exp	*ft_last_explst(t_exp *envlst);
void	ft_exp_add_back(t_exp **envlst, t_exp *toadd);
void	ft_exp_set(t_struct *cable);
size_t	ft_envlst_size(t_envlst *envlst);
void	ft_alpha_order(t_struct *cable);
char	*ft_exported_str(char *str, t_struct *cable);

#endif
