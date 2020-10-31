/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 20:03:41 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/31 18:01:57 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
#include "digest.h"
#include "main.h"
#include <errno.h>

t_digest_args	parse_digest_args(char *av[], t_digest *d)
{
	t_digest_args	a;

	a = (t_digest_args){d, false, false, false, false, false};
	while (*av)
	{
		if (!ft_strcmp(*av, "--"))
			a.file_mode = true;
		else if (a.file_mode == false && **av == '-')
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

t_digest		*get_digest(char *name)
{
	t_digest		*p;

	p = &g_digests[0];
	while (p != &g_digests[2])
	{
		if (!strcmp(p->arg_name, name))
			return (p);
		p = &p[1];
	}
	return (NULL);
}

int				digest_main(t_digest *d, char *argv[])
{
	parse_digest_args(&argv[2], d);
	return (0);
}
