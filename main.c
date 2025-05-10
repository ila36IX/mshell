#include "shell.h"

typedef t_list t_garbage_collector;

void *ft_malloc(size_t num, size_t size) {
        static t_garbage_collector *mock;
        void *allocated_mem;

        allocated_mem = ft_calloc(num, size);
        ft_lstadd_back(&mock, ft_lstnew(allocated_mem));
        return (allocated_mem);
}

/**
 * ft_isspace - checks for white-space characters
 *
 * @c: charachter to check
 * Return: TRUE if its a charachter and FALSE if not
 */
int ft_isspace(char c) {
        return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
        c == '\v');
}

char *extract_quote_content(char quote_type, char *input, t_token **tokens)
{
        int i;

        i = 0;
        token_lst_add_back(tokens, input++, 1);
        while (input[i] && input[i] != quote_type)
                i++;
        token_lst_add_back(tokens, input, i);
        input += i;
        if (*input == quote_type)
                token_lst_add_back(tokens, input++, 1);
        return (input);
}

int is_special(char c)
{
        return (c == '"' || c == '\'' || c == '>' || c == '<' || c == '$');
}

void parse(char *input)
{
        t_token *tokens;
        int i;

        tokens = NULL;
        while (input && *input)
        {
                i = 0;
                if (ft_isspace(*input))
                {
                        token_lst_add_back(&tokens, NULL, 0);
                        while (ft_isspace(*input))
                                input++;
                }
                else if (*input == '$')
                        token_lst_add_back(&tokens, input++, 1);
                else if (*input == '"' || *input == '\'')
                        input = extract_quote_content(*input, input, &tokens);
                else if (*input == '>') {
                        if (*(input + 1) == '>') {
                                token_lst_add_back(&tokens, input, 2);
                                input += 2;
                        } else
                        token_lst_add_back(&tokens, input++, 1);
                } else if (*input == '<') {
                        if (*(input + 1) == '<') {
                                token_lst_add_back(&tokens, input, 2);
                                input += 2;
                        } else
                        token_lst_add_back(&tokens, input++, 1);
                } else {
                        while (input[i] && !ft_isspace(input[i]) && !is_special(input[i]))
                                i++;
                        token_lst_add_back(&tokens, input, i);
                        input += i;
                }
        }
        token_lst_print(tokens);
        tokens = NULL;
}

int main(void) {
        char *cmd;

        while (1) {
                cmd = readline("minishell$ ");

                parse(cmd);
                if (ft_strcmp(cmd, "exit") == 0)
                        break;
                free(cmd);
        }
        return EXIT_SUCCESS;
}
