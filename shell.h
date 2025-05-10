#include "libft/libft.h"
#include <stdio.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_REDIRECTIONS 200
#define TRUE 1
#define FALSE 0
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

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

typedef struct s_token {
        char *token;
        int size;
        struct s_token *next;
} t_token;

void *ft_malloc(size_t num, size_t size);
void print_token_list(t_token *lst);
void	token_lst_add_back(t_token **lst, char *token, int size);
void	token_lst_print(t_token *lst);
