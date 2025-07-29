/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:04:00 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 19:04:02 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_PRINT_H
# define AST_PRINT_H

# include "../../types.h"

# define INDENT_SIZE 8

void		print_ast(t_ast *ast);
void		print_ast_connector(t_ast *ast, int indent);
void		print_ast_redirection(t_ast *ast, int indent);
void		print_ast_simple_cmd(t_ast *ast, int indent);
void		print_ast_subshell(t_ast *ast, int indent);
void		print_ast_type(t_ast *ast, int indent);

/* Internals */
void		_print_tree_end_root(int indent);
void		_print_ast_helper(t_ast *ast, int indent);
void		_tree_line_prefix(int indent, bool is_empty_line);

/* type printings */
const char	*ast_type_to_str(t_ast_type type);
const char	*connector_type_to_str(t_connector type);
const char	*redir_type_to_str(t_redirect_type type);
void		print_ast_redir_tokens(t_ast *ast, int indent);

#endif
