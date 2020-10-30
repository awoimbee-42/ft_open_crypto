/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:53:55 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/31 00:39:30 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
#include "main.h"
#include "digest/digest.h"
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
	void	*tmp;

	if (ac < 2 || !strcmp(av[1], "-h"))
		return usage(av[0]);
	if ((tmp = get_digest(av[1])))
		return (digest_main(tmp, av));
	ft_printf("%s: Error: '%s' is an invalid command.\n", av[0], av[1]);
	print_cmds();
	return 1;
}
