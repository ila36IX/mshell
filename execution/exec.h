#ifndef EXEC_H
# define EXEC_H

# include "./builtins/builtins.h"

char	*get_full_path(const char *cmd, char **envp);

#endif /* EXEC_H */
