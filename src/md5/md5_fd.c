/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:55:32 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/10 01:04:46 by awoimbee         ###   ########.fr       */
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

void	md5_file(t_global *g, char *fname)
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

void	padd_n_proc_chunk(t_global *g, char in[64], size_t len, size_t tot_len)
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

void	md5_fd(t_global *g, int filedesc, const char *fname)
{
	char		input[64];
	ssize_t		nb;
	uint64_t	input_size;

	ft_bzero(input, 64);
	input_size = 0;
	while (1)
	{
		nb = read(filedesc, input, 64);
		input_size += nb;
		if (nb != 64)
			break;
		md5_chunk(g, input);
	}
	if (nb == -1)
	{
		unset_hashing(g);
		ft_fprintf(2, "Could not read %s (%s)", fname, strerror(errno));
		return;
	}
	padd_n_proc_chunk(g, input, nb, input_size);
	char *s = md5_get_digest(g);
	ft_printf("%s\n", s);
	free(s);
}
