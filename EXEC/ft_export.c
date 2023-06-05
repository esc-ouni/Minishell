#include "minishell.h"

void	ft_replace_exp()
{

}

char	*ft_exported_str(char *str)
{
	char	**eq;
	char	*left;
	char	*right;

	eq = ft_soft_split_include(str, '=');
	left = ft_strjoin(ft_strdup("declare -x "), eq[0]);
	if (!eq[1][0] && !ft_strchr(eq[0], '='))
		return (left);
	right = ft_strjoin(ft_strdup("\""), eq[1]);
	right = ft_strjoin(right, "\"");
	left = ft_strjoin(left, right);
	return (left);
}

void	ft_export_env(t_struct *cable, char	*str)
{
	// if (exist)
	// 	replace
	// else
		ft_env_add_back(&cable->envlst, ft_env_new_node(str, cable));
}

void	ft_export_exp(t_struct *cable, char *str)
{
	char	*expstr;
	expstr = ft_exported_str(str);
	// if(exist)
	// 	replace
	// else
		ft_exp_add_back(&cable->exp, ft_exp_new_node(expstr, cable));
		free(expstr);
		ft_alpha_order(cable);
}

void	ft_export(t_struct *cable, char	*str)
{
	if (!ft_valid_var(str))
		return ;
	/*if += find join str with exist var , if !var , lst add back new one to both*/
	// if (ft_strnstr())
	/*if !strch '=' add lstback to exp solo*/
	if (ft_strchr(str, '='))
		ft_export_env(cable, str);
	ft_export_exp(cable, str);
}
