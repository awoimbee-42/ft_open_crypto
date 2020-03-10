/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:45:25 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/10 00:52:41 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

#include <stdbool.h>
#include <inttypes.h>


typedef struct	s_global
{
	uint32_t		hashes[8];
	bool			hashing;
	bool			quiet;
	bool			reverse;
}				t_global;

/*
**	The argument processing in md5 is abysmal & I have to reproduce it.
**	We process each arg one after the other (so no support for repeating args).
*/
typedef void(*t_arg_callback)(t_global *g, void *value);

/**
**	take_value: 0 == no, 1 == yes, 2 == multiple
*/
typedef struct	s_arg
{
	char			short_name;
	int				take_value;
	t_arg_callback	f;
}				t_arg;


/* args.c */
void		process_args(t_global *g, char **argv);

/* main.c */
char		*ft_md5(char **argv);

/* md5_fd.c */
void		md5_fd(t_global *g, int filedesc, const char *fname);
void		md5_stdin(t_global *g, void *fuck_c);
void		md5_file(t_global *g, char *fname);

/* md5.c */
char		*md5_get_digest(t_global *g);
void		md5_chunk(t_global *g, void *chunk);
void		unset_hashing(t_global *g);

#endif
