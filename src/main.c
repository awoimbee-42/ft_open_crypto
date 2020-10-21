/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:53:55 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/21 12:28:40 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>
#include <libft/ft_str.h>
#include <libft/ft_prtf.h>
#include <libft/ft_fd.h>

int		print_cmds()
{
	ft_putstr(
		"Standard commands:\n"
		"Message Digest commands:\n"
		"\t- md5\n"
		"\t- sha256\n"
		"Cipher commands:\n"
	);
	return 0;
}

int		usage(char *name)
{
	ft_printf("Usage: %s command [command opts] [command args]\n", name);
	print_cmds();
	return (0);
}

int		main(int ac, char *av[])
{
	t_main_cmd	cmds[2];
	t_main_cmd	*p;

	cmds[0] = (t_main_cmd){"md5", main_md5};
	cmds[1] = (t_main_cmd){"sha256", main_sha256};
	p = cmds;
	if (ac < 2 || !strcmp(av[1], "-h"))
		return usage(av[0]);
	while (p != &cmds[2])
	{
		if (!strcmp(av[1], p->name))
			return (p->fn(ac, av));
		p = &p[1];
	}
	ft_printf("%s: Error: '%s' is an invalid command.", av[0], av[1]);
	print_cmds();
	return 1;
}
