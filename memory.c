#include "./main.h"

typedef enum s_act
{
	CLEAR,
	INSERT
}	t_act;

static void	ft_gc_act(void *addr, t_act action)
{
	static t_list	*gc;
	t_list	*gc_node;
	if (action == CLEAR)
		ft_lstclear(&gc, free);
	else if (action == INSERT)
	{
		gc_node = ft_lstnew(addr);
		ft_lstadd_back(&gc, gc_node);
	}
	/*ft_gc_print(gc);*/
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

void	*ft_malloc(size_t	size, size_t unit)
{
	void	*addr;

	addr = ft_calloc(size, unit);
	ft_gcadd_back(addr);
	return (addr);
}

