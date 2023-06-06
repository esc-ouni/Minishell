#include "minishell.h"


char	*ft_exported_str(char *str, t_struct *cable)
{
	char	**eq;
	char	*left;
	char	*right;

	eq = ft_msoft_split_include(str, '=', cable);
	left = ft_mstrjoin(cable, "declare -x ", eq[0], NTMP);
	if (!eq[1][0] && !ft_strchr(eq[0], '='))
		return (left);
	right = ft_mstrjoin(cable, "\"", eq[1], TMP);
	right = ft_mstrjoin(cable, right, "\"", TMP);
	left = ft_mstrjoin(cable, left, right, NTMP);
	return (left);
}





int	ft_isplus(char *str)
{
	char	**eq;

	eq = ft_soft_split(str, '=');
	if (strchr(eq[0], '+'))
		return (ft_free_stringp(eq), 1);
	return (ft_free_stringp(eq), 0);
}

void	ft_joint_to_export(t_struct *cable, char **str)
{
	t_envlst	*exist;
	char		**spl;
	*str = ft_trim_char(*str, '+', cable);
	exist = ft_var_env_exist(cable->envlst, *str);
	if (exist)
	{
		spl = ft_soft_split(*str, '=');
		*str = ft_mstrjoin(cable, exist->str, spl[1], NTMP);
		ft_free_stringp(spl);
	}
}

void	ft_export(t_struct *cable, char	*str)
{
	if (!str)
		ft_print_exp(cable->exp);
	if (!ft_valid_var(str))
		return ;
	if (ft_isplus(str))
		ft_joint_to_export(cable, &str);
	if (ft_strchr(str, '='))
		ft_export_env(cable, str);
	ft_export_exp(cable, str);
}
