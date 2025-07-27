#include "./exec.h"
#include "../libft/libft.h"

int	**init_pipes(int *number_of_nodes, t_ast *ast)
{
	int	**pipes;

	*number_of_nodes = count_nodes(ast);
	pipes = ft_malloc(sizeof(int *), *number_of_nodes - 1);
	for (int i  = 0; i < *number_of_nodes - 1; i++)
		pipes[i] = ft_malloc(sizeof(int), PIPE_SIZE);
	for (int i = 0; i < *number_of_nodes - 1; i++)
		pipe(pipes[i]);
	return (pipes);
}

int	close_all_pipes(int **pipes, int count)
{
	int	i;

	if (pipes == NULL)
		return (ERR_NULL);
	i = 0;
	 while (i < count)
	 {
		 close(pipes[i][0]);
		 close(pipes[i][1]);
		 i++;
	 }
	 return (SUCCESS);
}

int	setup_pipes(int count, int **pipes, int number_of_nodes)
{
	if (pipes == NULL)
		return (ERR_NULL);
	if (count == 0)
		dup2(pipes[0][1], STDOUT_FILENO);
	else if (count < number_of_nodes - 1)
	{
        dup2(pipes[count -1][0], STDIN_FILENO);
        dup2(pipes[count][1], STDOUT_FILENO);
    }
	else
		dup2(pipes[count - 1][0], STDIN_FILENO);
	close_all_pipes(pipes, number_of_nodes - 1);
	return (SUCCESS);
}
