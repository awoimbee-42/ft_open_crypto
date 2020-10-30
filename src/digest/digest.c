/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 20:03:41 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/31 00:44:47 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
#include "digest.h"
#include "main.h"
#include <errno.h>

void t_digest_args_zero(t_digest_args *a)
{
	a->echo = false;
	a->quiet = false;
	a->rev = false;
}

/*
**	file  0
**	stdin 1
**	str   2
*/
void	print_res(
	const char *digest,
	const char *fname,
	const char *algo,
	t_digest_args *a,
	t_print_fmt fmt)
{
	if (a->quiet || fmt == FMT_STDIN)
		ft_printf("%s\n", digest);
	else if (fmt == FMT_FILE && a->rev)
		ft_printf("%s %s\n", digest, fname);
	else if (fmt == FMT_FILE)
		ft_printf("%s (%s) = %s\n", algo, fname, digest);
	else if (fmt == FMT_STR && a->rev)
		ft_printf("%s \"%s\"\n", digest, fname);
	else if (fmt == FMT_STR)
		ft_printf("%s (\"%s\") = %s\n", algo, fname, digest);
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
	print_res(out, NULL, a->d->print_name, a, FMT_STDIN);
}

void			do_str(t_digest_args *a, const char *str)
{
	t_fstream		*s;
	char			*out;

	a->did_something = true;
	ft_assert(str != NULL, "Missing string after '-s'\n");
	s = ft_fstream_setup_str(str, 64);
	out = a->d->fn(s, false);
	print_res(out, str, a->d->print_name, a, FMT_STR);
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
	print_res(out, fname, a->d->print_name, a, FMT_FILE);
}


t_digest_args parse_digest_args(char *av[], t_digest *d)
{
	t_digest_args	a;
	char			*out;

	t_digest_args_zero(&a);
	a.d = d;
	while (*av)
	{
		if (!ft_strcmp(*av, "--"))
			a.file_mode = true;
		else if (a.file_mode == false && **av == '-')
		{
			if (!ft_strcmp(&((*av)[1]), "p"))
				do_stdin(&a, true);
			else if (!ft_strcmp(&((*av)[1]), "q"))
				a.quiet = true;
			else if (!ft_strcmp(&((*av)[1]), "r"))
				a.rev = true;
			else if (!ft_strcmp(&((*av)[1]), "s"))
				do_str(&a, *(++av));
			else
				ft_printf("Unrecognised flag: %s\n", *av);
		}
		else
			do_file(&a, *av, d->arg_name);
		av = &av[1];
	}
	if (!a.did_something)
		do_stdin(&a, false);
	return (a);
}

static t_digest g_digests[] = {
	(t_digest){"md5", "MD5", md5_fd},
	(t_digest){"sha256", "SHA256", sha256_fd},
};

t_digest	*get_digest(char *name)
{
	t_digest	*p;

	p = &g_digests[0];
	while (p != &g_digests[2])
	{
		if (!strcmp(p->arg_name, name))
			return (p);
		p = &p[1];
	}
	return (NULL);
}

int		digest_main(t_digest *d, char *argv[])
{
	parse_digest_args(&argv[2], d);
	return 0;
}
