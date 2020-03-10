/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:56:27 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/10 00:57:41 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_md5.h"
#include <libft/ft_exit.h>

static const t_arg g_args[4] = {
	{'p', 0, md5_stdin}, // md5_stdin
	{'q', 0, NULL}, // enable_quiet w/ static var
	{'r', 0, NULL}, // set_reverse_output w/ static var
	{'s', 1, NULL}, // md5_str
};

static void	arg_callback(t_global *g, char *arg)
{
	const t_arg	*a;
	const t_arg	*end;

	if (*arg != '-')
	{
		md5_file(g, arg);
		return;
	}
	end = &g_args[4]; // FUCK YOU Warray-bounds FFS KYS ASKLFF
	while (*(++arg))
	{
		a = g_args;
		while (a <= end && a->short_name != *arg)
			++a;
		ft_assert(a <= end, "Invalid argument: %c", *arg);
		a->f(g, NULL);
	}
}

void		process_args(t_global *g, char **argv)
{
	if (!*argv)
		md5_stdin(g, NULL);
	while (*argv)
	{
		arg_callback(g, *argv);
		++argv;
	}
}
