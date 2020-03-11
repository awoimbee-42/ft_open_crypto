/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:45:25 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/11 14:09:37 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# define READ_BUF_SIZE 1024 * 1024
# if READ_BUF_SIZE % 64 != 0
#  error "pute"
# endif

# define NO_ARGS (void*)1

# include <sys/types.h>
# include <stdbool.h>
# include <inttypes.h>

typedef struct	s_global
{
	uint32_t		hashes[8];
	bool			hashing;
	bool			quiet;
	bool			reverse;
}				t_global;

/*
**	The argument processing in sha256 is abysmal & I have to reproduce it.
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

typedef struct	s_fcontent
{
	size_t			len;
	char			dat[READ_BUF_SIZE];
}				t_fcontent;

/* args.c */
void		sha256_proc_args(t_global *g, char **argv);

/* main.c */
char		*ft_sha256(char **argv);

/* sha256_fd.c */
void		sha256_fd(t_global *g, int filedesc, const char *fname);
void		sha256_print(t_global *g, int type, const char *fname);
void		sha256_pad_n_proc_c(t_global *g, char *in, size_t len, size_t tot_len);

/* callbacks.c */
void		sha256_stdin(t_global *g, void *fuck_c);
void		sha256_file(t_global *g, const char *fname);
void		sha256_str(t_global *g, void *str);

/* sha256.c */
char		*sha256_get_digest(t_global *g);
void		sha256_chunk(t_global *g, void *chunk);
void		sha256_unset_hashing(t_global *g);

#endif
