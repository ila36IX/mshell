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

int	main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	*line;
	t_lexer lexer;
	int		status;
	(void)(ac);
	(void)(av);

	while ((line = ft_readline(PROMPT)))
	{
		lexer = lexer_new(line, ft_strlen(line));
		ast = create_ast(&lexer);
		/* print_ast(ast); */
		exec_main(ast, envp);
		ft_gc_clear();
	}
	status = status_get();
	return (status);
}
