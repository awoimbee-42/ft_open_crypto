/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:32:11 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/11 19:01:41 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"
#include <libft/ft_mem.h>
#include <libft/ft_exit.h>
#include <stdlib.h>

void			md5_unset_hashing(t_global *g)
{
	ft_bzero(g->hashes, sizeof(g->hashes));
	g->hashing = false;
}

char			*md5_get_digest(t_global *g)
{
	const char	*str_base;
	char		*digest[2];
	uint8_t		*md5;
	int			v;

	str_base = "0123456789abcdef";
	md5 = (uint8_t*)g->hashes;
	ft_assertp_safe(digest[0] = malloc(33), "malloc failed", NULL);
	ft_memset(digest[0], '0', 32);
	digest[0][32] = '\0';
	digest[1] = digest[0];
	while (*digest[1])
	{
		v = *(md5++);
		digest[1][1] = str_base[v % 16];
		v /= 16;
		digest[1][0] = str_base[v % 16];
		digest[1] += 2;
	}
	md5_unset_hashing(g);
	return (digest[0]);
}
