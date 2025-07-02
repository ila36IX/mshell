# include "./main.h"
# include "./parser/parser.h"

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
	t_lexer	lexer;

	(void)ac;
	(void)av;
	while ((line = ft_readline("$ ")))
	{
		lexer = lexer_new(line, ft_strlen(line));
		ast = create_ast(&lexer);
		exec_main(ast, envp);
		/* print_ast(ast); */
	}
	return (0);
}
