/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:19:48 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 17:17:41 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../types.h"

t_ast	*ast_create(char *line);
bool		ast_expand(t_ast *ast);
void		print_ast(t_ast *ast);

#endif
