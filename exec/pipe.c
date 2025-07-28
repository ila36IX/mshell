/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:42:10 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 01:43:22 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "../libft/libft.h"

int	**init_pipes(int *number_of_nodes, t_ast *ast)
{
	int	**pipes;
	int	i;

	*number_of_nodes = count_nodes(ast);
	pipes = ft_malloc(sizeof(int *), *number_of_nodes - 1);
	i = 0;
	while (i < *number_of_nodes - 1)
	{
		pipes[i] = ft_malloc(sizeof(int), PIPE_SIZE);
		i++;
	}
	i = 0;
	while (i < *number_of_nodes - 1)
	{
		pipe(pipes[i]);
		i++;
	}
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
