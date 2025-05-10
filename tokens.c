#include "shell.h"

t_token	*token_lst_new(char *token, int size)
{
	t_token	*node;

	node = ft_malloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = token;
	node->size = size;
	node->next = NULL;
	return (node);
}

void	token_lst_add_back(t_token **lst, char *token, int size)
{
	t_token	*walk;
	t_token	*new;

	if (!lst)
		return ;
        new = token_lst_new(token, size);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	walk = *lst;
	while (walk->next)
		walk = walk->next;
	walk->next = new;
}

void	token_lst_print(t_token *lst)
{
	t_token	*walk;
        int i;
	
	walk = lst;
	if (!walk)
	{
		printf(RED "Empty token list" RESET "\n");
		return;
	}
	while (walk)
	{
                printf(CYAN"Size: %d\n"RESET, walk->size);
                i = 0;
                if (!walk->token)
                        printf(RED"(nil)"RESET);
                while (i < walk->size && walk->token)
                        printf("%c", walk->token[i++]);
                printf(RED"%c"RESET, '$');
		walk = walk->next;
                printf("\n");
	}
}
