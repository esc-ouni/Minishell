#include "minishell.h"

void	ft_init(int ac, char **av, char **ev, t_struct **cable)
{
	(void)ac;
	(void)av;
	*cable = (t_struct *)malloc(sizeof(t_struct));
	ft_env_set(*cable, ev);
}

void	program(t_struct *cable)
{
	
}

int	main(int ac, char **av, char **ev)
{
	t_struct	*cable;
	ft_init(ac, av, ev, &cable);
	while (1)
		program(cable);
}
