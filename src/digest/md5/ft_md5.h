/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:45:25 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/30 17:11:30 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# define NO_ARGS 1LU

# include <sys/types.h>
# include <stdbool.h>
# include <inttypes.h>

#include "../digest.h"

typedef struct	s_global_md5
{
	uint32_t			hashes[4];
	bool				hashing;
	t_fstream			*stream;
}				t_global_md5;

/*
**	md5_fd.c
*/
char			*md5_fd(t_fstream *s, bool echo);
void			md5_print(t_global_md5 *g, int type, const char *fname);
void			md5_pad_n_proc(t_global_md5 *g, uint8_t *in, size_t len, size_t flen);

/*
**	callbacks.c
*/
void			md5_stdin(t_global_md5 *g, void *fuck_c);
void			md5_file(t_global_md5 *g, const char *fname);
void			md5_str(t_global_md5 *g, void *str);

/*
**	md5.c
*/
void			md5_chunk(t_global_md5 *g, void *chunk);

/*
**	md5_utils.c
*/
void			md5_unset_hashing(t_global_md5 *g);
char			*md5_get_digest(t_global_md5 *g);

#endif
