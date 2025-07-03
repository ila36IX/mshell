/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:42:34 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 17:42:56 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../types.h"
#include "arrays.h"

#define INIT_ARGV_ARRAY_SIZE 3

static int	words_ensure_capacity(t_simple_cmd *scmd)
{
	size_t	required_capacity;
	size_t	new_capacity;
	char	**new_buff;

	required_capacity = scmd->argc + 1;
	if (scmd->capacity >= required_capacity)
		return (0);
	new_capacity = scmd->capacity * 2;
	if (new_capacity < required_capacity)
		new_capacity = required_capacity;
	new_buff = malloc(new_capacity * sizeof(char *));
	if (!new_buff)
		return (-1);
	ft_memcpy(new_buff, scmd->argv, scmd->argc * sizeof(char *));
	free(scmd->argv);
	scmd->argv = new_buff;
	scmd->capacity = new_capacity;
	return (0);
}

void	args_append(t_simple_cmd *scmd, char *arg)
{
	words_ensure_capacity(scmd);
	scmd->argv[scmd->argc++] = arg;
}

void	init_argv(t_simple_cmd *scmd)
{
	scmd->argc = 0;
	scmd->capacity = INIT_ARGV_ARRAY_SIZE;
	scmd->argv = ft_malloc(scmd->capacity, sizeof(char *));
}
