/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:55:32 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/10 02:20:28 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_md5.h"
#include <libft/ft_nb.h>
#include <libft/ft_mem.h>
#include <libft/ft_exit.h>
#include <stdlib.h>
#include <libft/ft_prtf.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void	md5_file(t_global *g, const char *fname)
{
	int		fd;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "Could not open %s (%s)", fname, strerror(errno));
		return;
	}
	md5_fd(g, fd, fname);
	ft_assert(close(fd) == 0, "Could not close file (%s)", fname);
}

void	md5_stdin(t_global *g, void *fuck_c)
{
	(void)fuck_c;
	md5_fd(g, STDIN_FILENO, "stdin");
}


static void	padd_n_proc_chunk(t_global *g, char in[64], size_t len, size_t tot_len)
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
		unset_hashing(g);
		ft_fprintf(2, "Could not read file %s (%s)", f, strerror(errno));
		return (1);
	}
	return (0);
}

void	md5_fd(t_global *g, int filedesc, const char *fname)
{
	t_fcontent	content;
	size_t		idx;
	uint64_t	tot_len;

	tot_len = 0;
	while (!read_file(g, filedesc, fname, &content))
	{
		tot_len += content.len;
		idx = 0;
		while (idx + 64 <= content.len)
		{
			md5_chunk(g, &content.dat[idx]);
			idx += 64;
		}
		if (!content.len || idx != content.len)
		{
			padd_n_proc_chunk(g, &content.dat[idx], content.len % 64, tot_len);
			char *s = md5_get_digest(g);
			ft_printf("%s\n", s);
			free(s);
			return;
		}
	}
}


#include <libft/ft_str.h>

void	md5_str(t_global *g, void *str)
{
	char		buf[64];
	char		*s;
	size_t		len;
	size_t		idx;

	s = str;
	len = ft_strlen(s);
	idx = 0;
	while (idx + 64 <= len)
	{
		md5_chunk(g, &s[idx]);
		idx += 64;
	}
	if (!len || idx != len)
	{
		ft_memcpy(buf, &s[idx], len % 64);
		padd_n_proc_chunk(g, buf, len % 64, len);
		char *s = md5_get_digest(g);
		ft_printf("%s\n", s);
		free(s);
		return;
	}
}
