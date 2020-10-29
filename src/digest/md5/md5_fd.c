/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:55:32 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/29 16:34:30 by awoimbee         ###   ########.fr       */
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

/*
**	file  0
**	stdin 1
**	str   2
*/

void		md5_print(t_global_md5 *g, int type, const char *fname)
{
	char	*digest;

	digest = md5_get_digest(g);
	if (g->args->quiet || type == 1)
		ft_printf("%s\n", digest);
	else if (type == 0 && g->args->rev_fmt)
		ft_printf("%s %s\n", digest, fname);
	else if (type == 0)
		ft_printf("MD5 (%s) = %s\n", fname, digest);
	else if (type == 2 && g->args->rev_fmt)
		ft_printf("%s \"%s\"\n", digest, fname);
	else if (type == 2)
		ft_printf("MD5 (\"%s\") = %s\n", fname, digest);
	free(digest);
}

void		md5_pad_n_proc(t_global_md5 *g, char *in, size_t cur_len, size_t read_len)
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

char		*md5_fd(const t_digest_args* args)
{
	t_global_md5	g;
	t_fstream		*fstream;

	ft_bzero(&g, sizeof(g));
	g.args = args;
	fstream = ft_fstream_setup_fd(g.args->fd, 64);
	while (ft_fstream(fstream))
	{
		if (args->fd == STDIN_FILENO)
			write(1, fstream->s.chunk, fstream->s.len);
		if (likely(fstream->s.len == 64))
			md5_chunk(&g, fstream->s.chunk);
		else {
			md5_pad_n_proc(&g, fstream->s.chunk, fstream->s.len, fstream->len_read);
		}
	}
	return (md5_get_digest(&g));
}
