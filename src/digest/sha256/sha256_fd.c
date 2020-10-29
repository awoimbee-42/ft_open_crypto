/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:55:32 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/29 16:34:20 by awoimbee         ###   ########.fr       */
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

/*
**	file  0
**	stdin 1
**	str   2
*/

void		sha256_print(t_global_sha256 *g, int type, const char *fname)
{
	char	*digest;

	digest = sha256_get_digest(g);
	if (g->args->quiet || type == 1)
		ft_printf("%s\n", digest);
	else if (type == 0 && g->args->rev_fmt)
		ft_printf("%s %s\n", digest, fname);
	else if (type == 0)
		ft_printf("SHA256 (%s) = %s\n", fname, digest);
	else if (type == 2 && g->args->rev_fmt)
		ft_printf("%s \"%s\"\n", digest, fname);
	else if (type == 2)
		ft_printf("SHA256 (\"%s\") = %s\n", fname, digest);
	free(digest);
}

void		sha256_pad_n_proc(t_global_sha256 *g, char *in, size_t len, size_t tot_len)
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

char		*sha256_fd(const t_digest_args *args)
{
	t_global_sha256	g;
	t_fstream		*fstream;

	ft_bzero(&g, sizeof(g));
	g.args = args;
	fstream = ft_fstream_setup_fd(g.args->fd, 64);
	while (ft_fstream(fstream))
	{
		if (args->fd == STDIN_FILENO)
			write(1, fstream->s.chunk, fstream->s.len);
		if (likely(fstream->s.len == 64))
			sha256_chunk(&g, fstream->s.chunk);
		else {
			sha256_pad_n_proc(&g, fstream->s.chunk, fstream->s.len, fstream->len_read);
		}
	}
	return (sha256_get_digest(&g));
}
