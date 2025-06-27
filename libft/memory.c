#include "./libft.h"

typedef enum s_act
{
	CLEAR,
	INSERT,
	REMOVE
}	t_act;

/*static void	ft_gcprint(t_list *gc)*/
/*{*/
/*	printf("-------------\n");*/
/*	while (gc)*/
/*	{*/
/*		printf("[%p]\n", gc->content);*/
/*		gc = gc->next;*/
/*	}*/
/*	printf("-------------\n");*/
/*}*/

static void	ft_gc_act(void *addr, t_act action)
{
	static t_list	*gc;
	t_list	*gc_node;

	if (action == CLEAR)
	{
		ft_lstclear(&gc, free);
		gc = NULL;
	}
	else if (action == INSERT)
	{
		if (ft_lstismember(gc, addr) == true)
			return ;
		gc_node = ft_lstnew(addr);
		ft_lstadd_back(&gc, gc_node);
	}
	else if (action == REMOVE)
		ft_lstdelone(addr, free);
}

void	*ft_malloc(size_t	size, size_t unit)
{
	void	*addr;

	addr = ft_calloc(size, unit);
	ft_gcadd_back(addr);
	return (addr);
}

void	ft_gcadd_back(void *addr)
{
	if (addr)
		ft_gc_act(addr, INSERT);
}

void	ft_gc_clear(void)
{
	ft_gc_act(NULL, CLEAR);
}

void	ft_gc_remove(void *addr)
{
	ft_gc_act(addr, REMOVE);
}

