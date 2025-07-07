/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:24:58 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/05 17:29:12 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "./includes.h"

typedef enum e_connector
{
	CONNECTOR_AND,
	CONNECTOR_PIPE,
	CONNECTOR_OR
}						t_connector;

typedef enum e_ast_type
{
	AST_SUBSHELL,
	AST_SIMPLE_COMMAND,
	AST_CONNECTOR,
	AST_INVALID,
}						t_ast_type;

typedef enum e_redirect_type
{
	REDIR_TYPE_IN,
	REDIR_TYPE_OUT,
	REDIR_TYPE_APPEND,
	REDIR_TYPE_HEREDOC
}						t_redirect_type;

/**
 * t_word - type represent a bash word that possibly contains quotes
 *
 * @text: text of the word
 * @len: size of len
 */
typedef struct s_word
{
	const char	*text;
	size_t		len;
}				t_word;

/**
 * s_words - dynamic array of words
 *
 * @buff: array of words
 * @capacity: capacity of the array
 * @length: number of items currently in the array
 */
typedef struct s_words
{
	t_word		*buff;
	size_t		capacity;
	size_t		length;
}				t_words;

/**
 * t_redirect - Mimics the behavior of dynamic array
 * to avoid the overhead caused when using linked-lists
 *
 * @type: Integer represinting redirection type see t_redirect_type
 * @target: Filename for <, >, >> Delimiter for <<
 * @tok_target: represents token that will be expanded into @target
 * @redirect_size: Current size of the array.
 */
typedef struct s_redirect
{
	t_redirect_type		type;
	char				*target;
	t_word				word_target;
}						t_redirect;

/**
 * s_simple_cmd - simple command is a array of arguments
 *
 * @argv: array of argument after expanding, that field is what execution module
 * must use
 * @tok_argv: array of words that will be expanded into argv
 * @argc: Number of arguments
 */
typedef struct s_simple_cmd
{
	char				**argv;
	t_words				tok_argv;
	size_t				argc;
	size_t				capacity;
}						t_simple_cmd;

/**
 * t_parse_err - type representing error details of a parting error
 *
 * @format - the error description
 * @tok: token that caused the parsing error
 * @tok_len: size of the token that caused the error
 */
typedef struct s_parse_err {
	const char *format;
	const char *tok;
	size_t tok_len;
} t_parse_err;

/*
 * NOTE: add docs here....
 */
typedef struct s_ast
{
	t_ast_type			type;
	union
	{
		t_connector		connector;
		t_parse_err		invalid_logs;
		t_simple_cmd	simple_cmd;
		struct s_ast	*subshell;
	};
	t_redirect			*redir;
	size_t				redir_size;
	size_t				redir_capacity;
	struct s_ast		*next;
}						t_ast;

#endif /* TYPES_H */
