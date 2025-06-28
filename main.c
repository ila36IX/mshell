# include "./main.h"
# include "./parser/parser.h"

# define PROMPT "\033[0;33m[User@Debian]$ \033[0m"

int	main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	*line;
	t_lexer lexer;
	(void)(ac);
	(void)(av);

	while ((line = readline(PROMPT)))
	{
		lexer = lexer_new(line, ft_strlen(line));
		ast = create_ast(&lexer);
		/* print_ast(ast); */
		exec_main(ast, envp);
	}
	return (0);
}
