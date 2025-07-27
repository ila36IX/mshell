/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:30 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:14:32 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GET 0
#define SET 1

/**
 * status_main - Gets/Sets the global status value based on an action
 * @action: GET or SET
 * @status: Pointer the value to act on
 */
static void	status_main(int action, int *status)
{
	static int	s_status;

	if (action == GET)
		*status = s_status;
	else if (action == SET)
	{
		s_status = *status;
	}
}

/**
 * status_get - Gets the global last exit status
 * Return: Value of the last exit status number
 */
int	status_get(void)
{
	int	status;

	status_main(GET, &status);
	return (status);
}

/**
 * status_set - Sets the global last exit status
 * @: status: Value to set
 */
void	status_set(int status)
{
	status_main(SET, &status);
}
