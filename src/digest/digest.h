/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:52:43 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/30 17:31:33 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIGEST_H
# define DIGEST_H

#include <stdbool.h>

typedef char*(*t_digest_fn)(t_fstream*, bool);

typedef struct	s_digest
{
	const char	*arg_name;
	const char	*print_name;
	t_digest_fn	fn;
}				t_digest;

typedef struct	s_digest_args
{
	const t_digest	*d;
	bool			echo;
	bool			quiet;
	bool			rev;
	bool			file_mode;
	bool			did_something;
}				t_digest_args;

typedef enum	e_print_fmt
{
	FMT_FILE,
	FMT_STDIN,
	FMT_STR,
}				t_print_fmt;

char			*md5_fd(t_fstream *s, bool echo);
char			*sha256_fd(t_fstream *s, bool echo);

#endif
