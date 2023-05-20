#include "Minishell.h"

int	searcher_for_spc(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$' && s[i] != '*' && s[i] != '+' && s[i] != '-' && s[i] != '>' && s[i] != '<' && s[i] != '\\' && s[i] != '!' && s[i] != '#' && s[i] != ' ' && s[i] != '\t' && s[i] != '\'')
		i++;
	return i;
}

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
			if (ft_strlen(node->cmd) == 1 && node->cmd[0] == '$')
				break ;
			else
			{
				i = 0;
				s = ft_msplit(collector, node->cmd, '$');
				if (node->cmd[0] != '$')
				{
					str = ft_mstrdup(collector, s[i]);
					i++;
				}
				while (s[i])
				{
					if (ft_isdigit(s[i][0]))
						str = ft_mstrjoin(collector, str, s[i]+1);
					else if (s[i][0] == '?')
					{
						str = ft_mstrjoin(collector, str, ft_itoa(g_exit_val));
						str = ft_mstrjoin(collector, str, s[i]+1);
					}
					else if (searcher_for_spc(s[i]))
					{
						l = searcher_for_spc(s[i]);
						str = ft_mstrjoin(collector, str, ft_getenv(collector, ft_msubstr(collector, s[i], 0, l), env));
						str = ft_mstrjoin(collector, str, s[i]+l);
					}
					else
						str = ft_mstrjoin(collector, str, ft_getenv(collector, s[i], env));
					i++;
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
