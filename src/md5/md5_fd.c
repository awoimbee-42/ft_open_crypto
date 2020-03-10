/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:55:32 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/10 17:45:03 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_md5.h"
#include <libft/ft_mem.h>
#include <libft/ft_exit.h>
#include <stdlib.h>
#include <libft/ft_prtf.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

/*
**	file  0
**	stdin 1
**	str   2
*/
void		md5_print(t_global *g, int type, const char *fname)
{
	char	*digest;

	digest = md5_get_digest(g);
	if (g->quiet || type == 1)
		ft_printf("%s\n", digest);
	else if (type == 0 && g->reverse)
		ft_printf("%s %s\n", digest, fname);
	else if (type == 0)
		ft_printf("MD5 (%s) = %s\n", fname, digest);
	else if (type == 2 && g->reverse)
		ft_printf("%s \"%s\"\n", digest, fname);
	else if (type == 2)
		ft_printf("MD5 (\"%s\") = %s\n", fname, digest);
	free(digest);
}

void		md5_pad_n_proc_c(t_global *g, char *in, size_t len, size_t tot_len)
{
	bool	one_not_written;

	one_not_written = 1;
	if (len >= 56) {
		one_not_written = 0;
		ft_bzero(&in[len], 64 - len);
		in[len] |= 1 << 7;
		md5_chunk(g, in);
		len = 0;
	}
	ft_bzero(&in[len], 64 - 8 - len);
	in[len] |= one_not_written ? 1 << 7 : 0;
	*((uint64_t*)&in[64 - 8]) = tot_len * 8;
	md5_chunk(g, in);
}

static int	read_file(t_global *g, int fd, const char *f, t_fcontent *content)
{
	content->len = read(fd, content->dat, READ_BUF_SIZE);
	if ((ssize_t)content->len == -1)
	{
		md5_unset_hashing(g);
		ft_fprintf(2, "Could not read file %s (%s)\n", f, strerror(errno));
		return (1);
	}
	return (0);
}

void		md5_fd(t_global *g, int filedesc, const char *fname)
{
	t_fcontent	content;
	size_t		idx;
	uint64_t	tot_len;

	tot_len = 0;
	while (!read_file(g, filedesc, fname, &content))
	{
		if (filedesc == STDIN_FILENO && fname != NO_ARGS)
			write(1, content.dat, content.len);
		tot_len += content.len;
		idx = 0;
		while (idx + 64 <= content.len)
		{
			md5_chunk(g, &content.dat[idx]);
			idx += 64;
		}
		if (!content.len || idx != content.len)
		{
			if (filedesc == STDIN_FILENO && fname != NO_ARGS)
				write(1, "\n", 1);
			md5_pad_n_proc_c(g, &content.dat[idx], content.len % 64, tot_len);
			md5_print(g, filedesc == STDIN_FILENO, fname);
			return;
		}
	}
}
