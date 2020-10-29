/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:45:25 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/29 16:30:20 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# define NO_ARGS 1LU

# include <sys/types.h>
# include <stdbool.h>
# include <inttypes.h>

#include "../digest.h"

typedef struct	s_global_sha256
{
	uint32_t			hashes[8];
	bool				hashing;
	const t_digest_args	*args;
}				t_global_sha256;


/*
**	sha256_fd.c
*/
char			*sha256_fd(const t_digest_args* args);
void			sha256_print(t_global_sha256 *g, int type, const char *fname);
void			sha256_pad_n_proc(t_global_sha256 *g, char *in, size_t len,
									size_t flen);

/*
**	callbacks.c
*/
void			sha256_stdin(t_global_sha256 *g, void *fuck_c);
void			sha256_file(t_global_sha256 *g, const char *fname);
void			sha256_str(t_global_sha256 *g, void *str);

/*
**	sha256.c
*/
char			*sha256_get_digest(t_global_sha256 *g);
void			sha256_chunk(t_global_sha256 *g, void *chunk);
void			sha256_unset_hashing(t_global_sha256 *g);

#endif
