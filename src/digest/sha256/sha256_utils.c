/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 19:10:22 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/29 16:34:16 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
#include "ft_sha256.h"
#include <libft/ft_mem.h>
#include <libft/ft_exit.h>
#include <libft/ft_nb.h>
#include <stdlib.h>

void			sha256_unset_hashing(t_global_sha256 *g)
{
	ft_bzero(g->hashes, sizeof(g->hashes));
	g->hashing = false;
}

char			*sha256_get_digest(t_global_sha256 *g)
{
	const char	*str_base;
	char		*digest[2];
	uint8_t		*sha256;
	uint		v;

	str_base = "0123456789abcdef";
	ft_assertp_safe(digest[0] = malloc(65), "malloc failed", NULL);
	ft_memset(digest[0], '0', 64);
	digest[0][64] = '\0';
	digest[1] = digest[0];
	v = -1;
	while (++v < sizeof(g->hashes) / sizeof(g->hashes[0]))
		g->hashes[v] = ft_swap_endian32(g->hashes[v]);
	sha256 = (uint8_t*)g->hashes;
	while (*digest[1])
	{
		v = *(sha256++);
		digest[1][1] = str_base[v % 16];
		v /= 16;
		digest[1][0] = str_base[v % 16];
		digest[1] += 2;
	}
	sha256_unset_hashing(g);
	return (digest[0]);
}
