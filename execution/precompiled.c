#include "../main.h"

/*TODO: Impelement this*/
char	*expand_probable_path(char *path)
{
	return (NULL);
}

/*TODO: Impelement this*/
static char	**get_probable_paths(char *str, char **envp)
{
	char	**probable_paths;
	int		i;

	if (!str || !envp)
		return (NULL);
	i  = 0;
	while (envp[i])
	{
		if (envp)
		i++;
	}
	while (envp[i])
	{
		probable_paths[i] = expand_probable_path(envp[i]);
		i++;
	}
	return (probable_paths);
}

/*TODO: Impelement this*/
char	*get_full_path(const char *cmd, char **envp)
{
	char	*full_path;
	char	**probable_paths;

	if (!cmd)
		return (NULL);
	return (NULL);
}
