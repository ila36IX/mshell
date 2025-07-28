/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:11:07 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:11:11 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

# define SUCCESS 0
# define NOT_PERMITTED 1
# define NO_SUCH_FILE 2
# define NOT_FOUND 127

int		status_get(void);
void	status_set(int status);
void	ft_clean(void);
#endif /* STATUS_H */
