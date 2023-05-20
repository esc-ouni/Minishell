#include "Minishell.h"

void	emplify(t_collector **collector, t_cmd *cmd, char **env)
{
    t_file	*h_file;
    t_cmd	*n_cmd;
    char	**menv;

	if (!cmd)
		return ;
    menv = mgetenv(collector, env);
    n_cmd = cmd;
	while (n_cmd)
	{
		n_cmd->num_cmds = ft_cmdsize(cmd);
		n_cmd->myenv = menv;
		if (n_cmd->cmd[0])
			n_cmd->builtflag = cmd_type(collector, n_cmd->cmd[0]);
		h_file = n_cmd->out_files;
		if (h_file)
		{
			while (h_file->next)
			{
				h_file->islast = 0;
				h_file = h_file->next;
			}
			h_file->islast = 1;
		}
		h_file = n_cmd->in_files;
		if (h_file)
		{
			while (h_file->next)
			{
				h_file->islast = 0;
				h_file = h_file->next;
			}
			h_file->islast = 1;
		}
		n_cmd = n_cmd->next;
	}
}

char	*ft_getenv(t_collector **collector, char *key, t_env **menv)
{
	t_env	*env;
	char *key_part;

	key_part = NULL;
	env = *menv;
	while (env)
	{
		key_part = ft_msplit(collector, env->str, '=')[0];
		if (!(ft_strncmp(key, key_part, ft_strlen(key))) && (ft_strlen(key) == ft_strlen(key_part)))
			return (ft_strchr(env->str, '=') + 1);
		key_part = NULL;
		env = env->next;
	}
	return (NULL);
}