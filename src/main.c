/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:53:55 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/19 19:22:22 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>
#include <libft/ft_str.h>
#include <libft/ft_prtf.h>

int		usage(char *name)
{
	ft_printf("Usage: %s command [command opts] [command args]\n", name);
	return (0);
}

int		main(int ac, char *av[])
{
	t_main_cmd	cmds[2];
	t_main_cmd	*p;

	cmds[0] = (t_main_cmd){"md5", main_md5};
	cmds[1] = (t_main_cmd){"sha256", main_sha256};
	p = cmds;
	if (ac > 1)
	{
		while (p != &cmds[2])
		{
			if (!strcmp(av[1], p->name))
				return (p->fn(ac, av));
			p = &p[1];
		}
	}
	return (usage(av[0]));
}
