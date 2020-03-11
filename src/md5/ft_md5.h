/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:45:25 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/11 18:33:04 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# define READ_BUF_SIZE 1048576
# if READ_BUF_SIZE % 64 != 0
#  error "pute"
# endif

# define NO_ARGS 1LU

# include <sys/types.h>
# include <stdbool.h>
# include <inttypes.h>

typedef struct	s_global
{
	uint32_t		hashes[4];
	bool			hashing;
	bool			quiet;
	bool			reverse;
}				t_global;

/*
**	The argument processing in md5 is abysmal & I have to reproduce it.
**	We process each arg one after the other (so no support for repeating args).
*/
typedef void(*t_arg_callback)(t_global *g, void *value);

/*
**	take_value: 0 == no, 1 == yes, 2 == multiple
*/
typedef struct	s_arg
{
	char			short_name;
	int				take_value;
	t_arg_callback	f;
}				t_arg;

typedef struct	s_fcontent
{
	size_t			len;
	char			dat[READ_BUF_SIZE];
}				t_fcontent;

/*
**	args.c
*/
void			md5_proc_args(t_global *g, char **argv);

/*
**	main.c
*/
char			*ft_md5(char **argv);

/*
**	md5_fd.c
*/
void			md5_fd(t_global *g, int filedesc, const char *fname);
void			md5_print(t_global *g, int type, const char *fname);
void			md5_pad_n_proc(t_global *g, char *in, size_t len, size_t flen);

/*
**	callbacks.c
*/
void			md5_stdin(t_global *g, void *fuck_c);
void			md5_file(t_global *g, const char *fname);
void			md5_str(t_global *g, void *str);

/*
**	md5.c
*/
void			md5_chunk(t_global *g, void *chunk);

/*
**	md5_utils.c
*/
void			md5_unset_hashing(t_global *g);
char			*md5_get_digest(t_global *g);

#endif
