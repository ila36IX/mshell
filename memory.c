#include "./main.h"

static void	ft_gc_print(t_list *gc)
{
	while (gc)
	{
		printf("\t[%p] --> [%s]\n", gc->content, (char *)gc->content);
		gc = gc->next;
	}
}

static void	ft_gc_clear(t_list *gc)
{
	ft_lstclear(&gc, free);
}

void	ft_gcadd_back(void *addr)
{
	static t_list	*g_collector;
	t_list	*gc_node;

	if (!addr)
	{
		ft_gc_print(g_collector);
		ft_gc_clear(g_collector);
		return ;
	}
	gc_node = ft_lstnew(addr);
	ft_lstadd_back(&g_collector, gc_node);
}


void	*ft_malloc(size_t	size, size_t unit)
{
	void	*addr;

	addr = ft_calloc(size, unit);
	ft_gcadd_back(addr);
	return (addr);
}

