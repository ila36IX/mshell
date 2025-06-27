#ifndef MEMORY_H
# define MEMORY_H

# include "../types.h"

void	*ft_malloc(size_t	size, size_t unit);
void	ft_gcadd_back(void *addr);
void	ft_gc_clear(void);
#endif /* MEMORY_H */
