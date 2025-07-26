/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:46:53 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 17:03:53 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec/status.h"
#include "ast_parser.h"

/**
 * parse_clean - create the ast from the user prompt
 *
 * @line: the readed line from the user
 *
 * Return: valid ast or NULL if line is empty or error found
 * - if parsing error found, the exit status will be set to 2
 */
t_ast	*ast_create(char *line)
{
	t_ast	*ast;
	t_lexer	lexer;

	if (!line)
		return (NULL);
	lexer = lexer_new(line, ft_strlen(line));
	ast = ast_parse_tree(&lexer);
	if (ast_check_errors(ast) == false)
	{
		status_set(PARSE_ERROR_STATUS_CODE);
		return (NULL);
	}
	return (ast);
}
