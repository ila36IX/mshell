
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:29:51 by sboukiou          #+#    #+#             */
/*   Updated: 2025/05/15 13:29:52 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "./includes.h"
# include "./lexer.h"
# include "./prototypes.h"
# include "./types.h"
# include "libft/libft.h"

# define UNIMPLEMENTED(...)                                                  \
	printf("%s:%d: UNIMPLEMENTED: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);

# define UNREACHABLE(...)                                                  \
	printf("%s:%d: UNREACHABLE: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);

# define TODO(...)                                                  \
	printf("%s:%d: TODO: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);

# define PANIC(...)                                                  \
	printf("%s:%d: PANIC: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);

#endif
