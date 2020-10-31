/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_digest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:54:29 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/31 22:57:23 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "digest.h"
#include <libft/ft_prtf.h>
#include <libft/ft_exit.h>
#include <errno.h>

/*
**	file  0
**	stdin 1
**	str   2
*/

static void		print_res(
	char *digest,
	const char *fname,
	t_digest_args *a,
	t_print_fmt fmt)
{
	if (a->quiet || fmt == FMT_STDIN)
		ft_printf("%s\n", digest);
	else if (fmt == FMT_FILE && a->rev)
		ft_printf("%s %s\n", digest, fname);
	else if (fmt == FMT_FILE)
		ft_printf("%s (%s) = %s\n", a->d->print_name, fname, digest);
	else if (fmt == FMT_STR && a->rev)
		ft_printf("%s \"%s\"\n", digest, fname);
	else if (fmt == FMT_STR)
		ft_printf("%s (\"%s\") = %s\n", a->d->print_name, fname, digest);
	free(digest);
}

void			do_stdin(t_digest_args *a, bool echo)
{
	t_fstream		*s;
	char			*out;

	a->did_something = true;
	if (echo)
		a->echo = echo;
	s = ft_fstream_setup_fd(0, 64);
	out = a->d->fn(s, a->echo);
	print_res(out, NULL, a, FMT_STDIN);
}

void			do_str(t_digest_args *a, const char *str)
{
	t_fstream		*s;
	char			*out;

	a->did_something = true;
	ft_assert(str != NULL, "Missing string after '-s'\n");
	s = ft_fstream_setup_str(str, 64);
	out = a->d->fn(s, false);
	print_res(out, str, a, FMT_STR);
}

void			do_file(t_digest_args *a, const char *fname, const char *cmd)
{
	t_fstream		*s;
	char			*out;

	a->file_mode = true;
	a->did_something = true;
	s = ft_fstream_setup_fname(fname, 64);
	if (!s)
	{
		ft_printf("ft_ssl: %s: %s: %s\n", cmd, fname, strerror(errno));
		return ;
	}
	out = a->d->fn(s, false);
	print_res(out, fname, a, FMT_FILE);
}
