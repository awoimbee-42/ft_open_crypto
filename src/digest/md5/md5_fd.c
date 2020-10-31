/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:55:32 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/31 18:03:27 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
#include <unistd.h>
#include "ft_md5.h"
#include <libft/ft_mem.h>
#include <libft/ft_exit.h>
#include <stdlib.h>
#include <libft/ft_prtf.h>
#include <libft/t_fstream.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static void	md5_pad_n_proc(
	t_global_md5 *g,
	uint8_t *in,
	size_t cur_len,
	size_t read_len)
{
	bool	one_not_written;

	one_not_written = 1;
	if (cur_len >= 56)
	{
		one_not_written = 0;
		ft_bzero(&in[cur_len], 64 - cur_len);
		in[cur_len] |= 1 << 7;
		md5_chunk(g, in);
		cur_len = 0;
	}
	ft_bzero(&in[cur_len], 64 - 8 - cur_len);
	in[cur_len] |= one_not_written ? 1 << 7 : 0;
	*((uint64_t*)&in[64 - 8]) = read_len * 8;
	md5_chunk(g, in);
}

char		*md5_fd(t_fstream *s, bool echo)
{
	t_global_md5	g;

	ft_bzero(&g, sizeof(g));
	g.stream = s;
	while (ft_fstream_autofree(&s))
	{
		if (echo)
			write(1, s->s.buf, s->s.len);
		if (__builtin_expect(s->s.len == 64, true))
			md5_chunk(&g, s->s.buf);
		else
			md5_pad_n_proc(&g, s->s.buf, s->s.len, s->s.total_len);
	}
	return (md5_get_digest(&g));
}
