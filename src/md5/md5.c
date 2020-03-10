/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:57:50 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/10 00:54:09 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"
#include <stdint.h>
#include <libft/ft_mem.h>
#include <libft/ft_prtf.h>
#include <stdlib.h>
#include <libft/ft_exit.h>

/* binary integer part of the sines of integers (Radians) as constants */
static const uint32_t	constants[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

static const uint32_t	g_round_shift[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
};

static uint32_t leftrotate(uint32_t x, uint32_t round)
{
	uint32_t	shift;

	shift = g_round_shift[round];
	return (
		(x << shift) | (x >> (32 - shift))
	);
}

static void	set_hashing(t_global *g)
{
	if (g->hashing)
		return;
	g->hashing = true;
	g->hashes[0] = 0x67452301;
	g->hashes[1] = 0xefcdab89;
	g->hashes[2] = 0x98badcfe;
	g->hashes[3] = 0x10325476;
}

void		unset_hashing(t_global *g)
{
	ft_bzero(g->hashes, sizeof(g->hashes));
	g->hashing = false;
}

char		*md5_get_digest(t_global *g)
{
	const char	*str_base;
	char		*digest[2];
	uint8_t		*md5;

	str_base = "0123456789abcdef";
	md5 = (uint8_t*)g->hashes;
	ft_assertp_safe(digest[0] = malloc(33), "malloc failed", NULL);
	ft_memset(digest[0], '0', 32);
	digest[0][32] = '\0';
	digest[1] = digest[0];
	while (*digest[1])
	{
		int v = *(md5++);
		digest[1][1] = str_base[v % 16];
		v /= 16;
		digest[1][0] = str_base[v % 16];
		digest[1] += 2;
	}
	unset_hashing(g);
	return digest[0];
}

// first, dumb implementation
void		md5_chunk(t_global *g, void *chunk)
{
	uint32_t	*chunk32;
	uint32_t	hash[4];
	int			i;

	chunk32 = chunk;
	set_hashing(g);
	ft_memcpy(hash, g->hashes, 4 * 4);
	i = -1;
	while (++i < 64)
	{
		uint32_t F, g;
		if (i < 16)
		{
			F = (hash[1] & hash[2]) | ((~hash[1]) & hash[3]);
			g = i;
		}
		else if (i < 32)
		{
			F = (hash[3] & hash[1]) | ((~hash[3]) & hash[2]);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			F = hash[1] ^ hash[2] ^ hash[3];
			g = (3 * i + 5) % 16;
		}
		else
		{
			F = hash[2] ^ (hash[1] | (~hash[3]));
			g = (7 * i) % 16;
		}
		F += hash[0] + constants[i] + chunk32[g];
		hash[0] = hash[3];
		hash[3] = hash[2];
		hash[2] = hash[1];
		hash[1] += leftrotate(F, i);
	}
	g->hashes[0] += hash[0];
	g->hashes[1] += hash[1];
	g->hashes[2] += hash[2];
	g->hashes[3] += hash[3];
}
