/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:25:34 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/30 09:25:34 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

void	string_append_nbr(t_string *s, int nb)
{
	unsigned int	n;

	if (nb < 0)
	{
		n = nb * -1;
		string_append_char(s, '-');
	}
	else
		n = nb;
	if (n > 9)
		string_append_nbr(s, n / 10);
	string_append_char(s, n % 10 + '0');
}
