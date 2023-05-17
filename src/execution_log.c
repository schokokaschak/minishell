/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_log.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:47:19 by akashets          #+#    #+#             */
/*   Updated: 2023/04/02 20:27:42 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

// void	execution(t_data *data)
// {
// 	t_log_groups	*buf;

// 	buf = data->log_groups;
// 	while (buf)
// 	{
// 		execute_pipes(&buf->pipe_groups, data);
// 		buf = buf->next;
// 	}
// }

int	sub_execute_log_recursion(t_log_groups **log_grp, t_data *data, \
														int cur_level)
{
	*log_grp = execution(data, *log_grp, cur_level + 1);
	if (*log_grp)
		return (1);
	else
		return (0);
}

void	*execution(t_data *data, t_log_groups *log_group, int cur_level)
{
	t_log_groups	*lt;
	int				lock;

	lt = log_group;
	lock = OPENED;
	while (lt)
	{
		if (lt->rec_depth > cur_level)
			if (!sub_execute_log_recursion(&lt, data, cur_level))
				return (NULL);
		if (lt->needed == -1 || (data->last_log_ret == 0 && lt->needed == 1) \
			|| (data->last_log_ret != 0 && lt->needed == 0))
		{
			if (lock == OPENED && !(execute_pipes(&lt->pipe_groups, data)))
				return (NULL);
		}
		else if (lt->rec_depth != 0 && lt->needed == 1 && \
						data->last_log_ret != 0)
			lock = CLOSED;
		if (lt->next && lt->next->rec_depth < cur_level)
			return (lt->next);
		lt = lt->next;
	}
	return (NULL);
}
