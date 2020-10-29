/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:52:43 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/29 16:30:44 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIGEST_H
# define DIGEST_H

#include <stdbool.h>

typedef struct	s_digest_args
{
	bool		echo;
	bool		quiet;
	bool		rev_fmt;
	bool		from_argv;
	int			fd;
	char		*fname;
}				t_digest_args;

typedef char*(*t_digest_fn)(const t_digest_args*);

struct s_digest_fn_from_str {
	char		*name;
	t_digest_fn	*fn;
};

char		*md5_fd(const t_digest_args* args);
char		*sha256_fd(const t_digest_args* args);

#endif
