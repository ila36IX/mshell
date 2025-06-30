#ifndef MEMORY_H
# define MEMORY_H

# include "../types.h"

void	*ft_malloc(size_t	size, size_t unit);
void	ft_gcadd_back(void *addr);
void	ft_gc_clear(void);
void ft_gc_remove_ft_split(char **list);
void	ft_gc_remove(void *addr);
/* For debuggin purposes */
void	ft_gcprint(void);
#endif /* MEMORY_H */
