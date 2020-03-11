/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subcommand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:02:25 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/11 18:37:46 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <libft/ft_str.h>

const struct s_cmds g_cmds[] = {
	{"md5", main_md5},
	{"sha256", main_sha256},
	{NULL, NULL},
};

t_subcmd	*get_subcmd(char *requested_cmd)
{
	const struct s_cmds	*cmds;

	if (requested_cmd == NULL)
		return (NULL);
	cmds = &g_cmds[0];
	while (cmds->name)
	{
		if (ft_strcmp(requested_cmd, cmds->name) == 0)
			return (cmds->fn_ptr);
		++cmds;
	}
	return (NULL);
}
