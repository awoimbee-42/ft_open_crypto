/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:56:27 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/10 12:20:15 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_md5.h"
#include <libft/ft_exit.h>

void	set_reverse(t_global *g, void *nothing);
void	set_quiet(t_global *g, void *nothing);

static const t_arg g_args[4] = {
	{'p', 0, md5_stdin}, // md5_stdin
	{'q', 0, set_quiet}, // enable_quiet w/ static var
	{'r', 0, set_reverse}, // set_reverse_output w/ static var
	{'s', 1, md5_str}, // md5_str
};

void	set_quiet(t_global *g, void *nothing)
{
	(void)nothing;
	g->quiet = true;
}

void	set_reverse(t_global *g, void *nothing)
{
	(void)nothing;
	g->reverse = true;
}

static void	arg_callback(t_global *g, char ***argv)
{
	const t_arg	*a;
	const t_arg	*end;
	const char	*arg;

	arg = **argv;
	if (*arg != '-')
	{
		md5_file(g, arg);
		return;
	}
	end = &g_args[4];
	while (*(++arg))
	{
		a = g_args;
		while (a <= end && a->short_name != *arg)
			++a;
		ft_assert(a <= end, "Invalid argument: %s", **argv);
		if (a->take_value == 0)
			a->f(g, NULL);
		else
		{
			ft_assert(*++arg == '\0', "Invalid argument: %s", **argv);
			++*argv;
			a->f(g, **argv);
			return;
		}
	}
}

void		process_args(t_global *g, char **argv)
{
	if (!*argv)
		md5_stdin(g, NO_ARGS);
	while (*argv)
	{
		arg_callback(g, &argv);
		++argv;
	}
}
