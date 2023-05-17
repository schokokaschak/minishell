/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:17:26 by nradin            #+#    #+#             */
/*   Updated: 2023/04/02 16:36:12 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	builtin_pwd(void)
{
	char	cwd[256];
	int		ret;

	if (getcwd(cwd, sizeof(cwd)))
		ret = 0;
	else
		ret = 1;
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (ret);
}
