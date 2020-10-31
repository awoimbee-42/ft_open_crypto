/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:52:43 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/31 18:01:06 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIGEST_H
# define DIGEST_H

# include <stdbool.h>
# include <libft/t_fstream.h>

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

t_digest		*get_digest(char *name);
int				digest_main(t_digest *d, char *argv[]);
char			*md5_fd(t_fstream *s, bool echo);
char			*sha256_fd(t_fstream *s, bool echo);

void			do_stdin(t_digest_args *a, bool echo);
void			do_str(t_digest_args *a, const char *str);
void			do_file(t_digest_args *a, const char *fname, const char *cmd);

#endif
