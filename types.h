/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:24:58 by sboukiou          #+#    #+#             */
/*   Updated: 2025/05/15 13:33:08 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "./includes.h"

typedef enum {
    FALSE = 0,
    TRUE = 1,
} t_bool;

typedef enum {
    OP_AND,
    OP_OR
} t_op_type;

typedef enum {
    REDIR_TYPE_IN,
    REDIR_TYPE_OUT,
    REDIR_TYPE_APPEND,
    REDIR_TYPE_HEREDOC
} t_redirect_type;

/**
 * t_redirect - Linked list describing a redirections of command
 * 
 * @type: Integer represinting redirection type see t_redirect_type
 * @target: Filename for <, >, >> Delimiter for <<
 * @next: next user redirection or NULL if no any exist
 */
typedef struct s_redirect {
    t_redirect_type type;
    char *target;       // Filename for <, >, >> Delimiter for <<.
    struct s_redirect *next; // Linked list for multiple redirections
} t_redirect;

/**
 * t_cmd - is linked list node that will represent a chain of commands
 * conncted by operators
 *
 * @args: array of strings first string is the cmd itself, and 1+ are
 * arguments
 * @arg: Number of arguments including the cmd
 * @redirects: What a redirection descriptor looks like
 * @next: next command ofter the pipe operator, or NULL
 * @prev: previous command before the pipe operator
 */
typedef struct s_cmd
{
	char	**argv;
	int	argc;
	t_redirect	*redir;
	struct s_cmd *next;
}	t_cmd;

/*
 * t_node: is node that represent a single command with its following sibling
 * command or sub-expression
 *
 * @next_op: which operator (|| or &&) connects this node to the next node
 * @next: pointer to the next node at the same level (the sibling)
 * @child_op: which operator connects this node down to its child sub-expression (inside parentheses)
 * @child:sub‐pointer to the first node in that sub-expression
 * @cmd: the actual command
 * Follow next (using next_op) to see siblings joined by || or &&
 * Follow child (using child_op) into any grouped sub-expression
 */
typedef struct s_node {
    t_op_type *next_op;
    struct s_node *next;
    t_op_type *child_op;
    struct s_node *child;
    t_cmd *cmd;
} t_node;


#endif
