/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:45:25 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/31 18:11:38 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# define NO_ARGS 1LU

# include <sys/types.h>
# include <stdbool.h>
# include <inttypes.h>

# include "../digest.h"

typedef struct	s_global_sha256
{
	uint32_t			hashes[8];
	bool				hashing;
	t_fstream			*stream;
}				t_global_sha256;

/*
**	sha256_fd.c
*/
char			*sha256_fd(t_fstream *s, bool echo);

/*
**	sha256.c
*/
char			*sha256_get_digest(t_global_sha256 *g);
void			sha256_chunk(t_global_sha256 *g, void *chunk);
void			sha256_unset_hashing(t_global_sha256 *g);

#endif
