#include <stdio.h>
#include "libft/libft.h"
#define MAX_REDIRECTIONS 200

typedef enum {
        TYPE_PIPE,
        TYPE_AND,
        TYPE_OR
} t_operators;

/**
 * t_redirect - Structure describing a redirections of command
 *
 * @input: chain of filenames that provided after the '<' operator
 * @output: chain of filenames that provided after the '>' operator
 * @last_input_type: integer represeting the type of writting to the last file
 * in @output array, 0 to overwrite, 1 to append
 */
typedef struct redirect
{
        char *inputs[MAX_REDIRECTIONS];
        int last_input_type; /* >> or > */
        char **outputs[MAX_REDIRECTIONS];
        char **her_doc_eof[MAX_REDIRECTIONS];
} t_redirect;

/**
 * t_command - is linked list node that will represent a chain of commands
 * conncted by operators
 *
 * @cmd_and_args: array of strings first string is the cmd itself, and 1+ are
 * arguments
 * @redirects: What a redirection descriptor looks like
 * @next: next command ofter the operator, or NULL
 * @prev: previous command before the operator
 * next_op: the operator the follows this command
 */
typedef struct s_command {
        char **cmd_and_args;
        t_redirect *redirects;
        struct s_command* next;
        struct s_command* prev;
        t_operators next_op;  // Operator following this command
} t_command;
