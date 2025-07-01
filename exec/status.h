#ifndef STATUS_H
# define STATUS_H

# define SUCCESS 0
# define NOT_PERMITTED 1
# define NO_SUCH_FILE 2
# define NOT_FOUND 127

int	status_get(void);
void	status_set(int status);
#endif /* STATUS_H */
