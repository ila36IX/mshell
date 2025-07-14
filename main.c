# include "./main.h"
# include "./parser/parser.h"
# include "./exec/status.h"
# define PROMPT "\033[0;33m[User@Debian]$ \033[0m"

static char	*ft_readline(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		return (NULL);
	ft_gcadd_back(line);
	return (line);
}

int	main(int ac, const char **av, const char **envp)
{
	t_ast	*ast;
	char	*line;
	int		status;
	(void)(ac);
	(void)(av);

	environ_init(envp);
	while ((line = ft_readline(PROMPT)))
	{
		add_history(line);
		ast =ast_create(line);
		exec(ast);
	}
	status = status_get();
	return (status);
}
