/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:56:27 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/09 16:01:17 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_md5.h"

const t_arg args[] = {
	{'p', 0, md5_stdin}, // md5_stdin
	{'q', 0, NULL}, // enable_quiet w/ static var
	{'r', 0, NULL}, // set_reverse_output w/ static var
	{'s', 1, NULL}, // md5_str
	{0, 0, NULL}, // md5_file -> special catch-all case
};

#include <libft/ft_str.h>
#include <libft.h>

static void	arg_callback(char *arg)
{
	const t_arg	*a;

	if (*arg != '-')
	{
		md5_file(arg); // TODO
		return;
	}
	while (*(++arg))
	{
		a = args;
		while (a->short_name && a->short_name != *arg)
			++a;
		ft_assert(a->short_name != 0, "Invalid argument: %c", *arg);
		a->f(NULL);
	}
}

void		process_args(char **argv)
{
	if (!*argv)
		md5_stdin();
	while (*argv)
	{
		arg_callback(*argv);
		++argv;
	}
}
