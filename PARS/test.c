#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	**mgetenv(char **env)
{
	int		i = 0;
	char	**new_env;

	while (env[i])
        i++;
	new_env = malloc(sizeof(char *) * (i + 1));
    i = -1;
	while(env[++i])
		new_env[i] = strdup(env[i]);
	new_env[i] = NULL;
	return (new_env);
}

int main(int a, char **v, char **env)
{
    int i = 0;
    char    **new_env = mgetenv(env);
    while(*env)
    {
        printf("%s\n", *env);
        env++;
    }
    printf("\n\nMINE:\n\n\n\n");
    while(new_env[i])
    {
        printf("%s\n", new_env[i++]);
    }
}