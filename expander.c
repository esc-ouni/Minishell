#include "Minishell.h"

void	expander(t_collector **collector, t_env **env, t_lexer **head)
{
	t_lexer	*node;
	int		i;
	int		l;
	int		k;

	k = 0;
	i = 0;
	l = 0;
	char **s;
	char *str;
	s = NULL;
	str = NULL;
	node = *head;
	while (node)
	{
		if ((node->type != ST_SQ) && (ft_strchr(node->cmd, '$')))
		{
			if (node->cmd[0] == '$')
			{
				if (ft_strlen(node->cmd) == 1)
					break ;
				else
				{
					i = 0;
					s = ft_msplit(collector, node->cmd, '$');
					while (s[i])
					{
						if (s[i][0] == '?')
						{
							str = ft_mstrjoin(collector, str, ft_itoa(g_exit_val));
							str = ft_mstrjoin(collector, str, s[i]+1);
						}
						else
							str = ft_mstrjoin(collector, str, ft_getenv(collector, s[i], env));
						i++;
					}
				}
			}
			else
			{
				if (node->cmd[0] == '\'')
					k = 1;
				i = 0;
				s = ft_msplit(collector, node->cmd, '$');
				str = ft_mstrdup(collector, s[i]);
				i++;
				while (s[i])
				{
					if (s[i][0] == '?')
					{
						str = ft_mstrjoin(collector, str, ft_itoa(g_exit_val));
						str = ft_mstrjoin(collector, str, s[i]+1);
					}
					else
						str = ft_mstrjoin(collector, str, ft_getenv(collector, ft_mstrtrim(collector, s[i], "'"), env));
					i++;
				}
				if (k)
				{
					str = ft_mstrjoin(collector, str, "'");
					k = 0;
				}
			}
			if (node->cmd[ft_strlen(node->cmd)-1] == '$')
				str = ft_mstrjoin(collector, str, "$");
			node->cmd = ft_mstrdup(collector, str);
		}
		str = NULL;
		s = NULL;
		node = node->next;
	}
}
