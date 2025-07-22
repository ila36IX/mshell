# include "./main.h"
# include "./parser/parser.h"
# include "./exec/status.h"
# define PROMPT "\033[0;33m[User@Debian]$ \033[0m"

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	status_set(130);
}

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
		exit(130);
}

static char	*ft_readline(const char *prompt)
{
	char	*line;

	/* if (isatty(STDIN_FILENO) == false)
		prompt = NULL; */
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

	signal(SIGINT, signal_handler);
	/* signal(SIGQUIT, signal_handler); */
	environ_init(envp);
	while ((line = ft_readline(PROMPT)))
	{
		add_history(line);
		ast =ast_create(line);
		/* print_ast(ast); */
		exec(ast);
	}
	status = status_get();
	return (status);
}
