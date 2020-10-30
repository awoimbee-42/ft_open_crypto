/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:55:32 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/30 23:50:54 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
#include "ft_sha256.h"
#include <libft/ft_exit.h>
#include <libft/ft_mem.h>
#include <libft/ft_nb.h>
#include <libft/ft_prtf.h>
#include <libft/t_fstream.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void		sha256_pad_n_proc(t_global_sha256 *g, uint8_t *in, size_t len, size_t tot_len)
{
	bool	one_not_written;

	one_not_written = 1;
	if (len >= 56)
	{
		one_not_written = 0;
		ft_bzero(&in[len], 64 - len);
		in[len] |= 1 << 7;
		sha256_chunk(g, in);
		len = 0;
	}
	ft_bzero(&in[len], 64 - 8 - len);
	in[len] |= one_not_written ? 1 << 7 : 0;
	*((uint64_t*)&in[64 - 8]) = ft_swap_endian64(tot_len * 8);
	sha256_chunk(g, in);
}

char			*sha256_fd(t_fstream *s, bool echo)
{
	t_global_sha256	g;

	ft_bzero(&g, sizeof(g));
	g.stream = s;
	while (ft_fstream_autofree(&s))
	{
		if (echo)
			write(1, s->s.buf, s->s.len);
		if (__builtin_expect(s->s.len == 64, true))
			sha256_chunk(&g, s->s.buf);
		else {
			sha256_pad_n_proc(&g, s->s.buf, s->s.len, s->s.total_len);
		}
	}
	return (sha256_get_digest(&g));
}
