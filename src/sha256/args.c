/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:56:27 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/11 19:02:49 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_sha256.h"
#include <libft/ft_exit.h>
#include <libft/ft_str.h>

static void			set_quiet(t_global *g, void *nothing)
{
	(void)nothing;
	g->quiet = true;
}

static void			set_reverse(t_global *g, void *nothing)
{
	(void)nothing;
	g->reverse = true;
}

static const t_arg g_args[4] = {
	{'p', 0, sha256_stdin},
	{'q', 0, set_quiet},
	{'r', 0, set_reverse},
	{'s', 1, sha256_str},
};

static uintptr_t	match_arg(t_global *g, char *const *const arg)
{
	const t_arg	*a;
	char		*s;

	s = *arg;
	if (s[0] == '\0')
		return (0);
	while (*(++s))
	{
		a = g_args;
		while (a <= &g_args[4] && a->short_name != *s)
			++a;
		ft_assert(a <= &g_args[4], "Invalid argument: %s", *arg);
		if (a->take_value == 0)
			a->f(g, NULL);
		else
		{
			ft_assert(*++s == '\0', "Invalid argument: %s", *arg);
			a->f(g, arg[1]);
			return (1);
		}
	}
	return (0);
}

void				sha256_proc_args(t_global *g, char **argv)
{
	bool	filemode;

	if (!*argv)
		sha256_stdin(g, (void*)NO_ARGS);
	filemode = false;
	--argv;
	while (*(++argv))
	{
		if ((ft_strcmp(*argv, "--") == 0 && !filemode) && (filemode = true))
			continue;
		else if ((**argv != '-' || filemode == true) && (filemode = true))
			sha256_file(g, *argv);
		else
			argv += match_arg(g, argv);
	}
}
