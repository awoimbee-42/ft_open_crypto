/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:05:22 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/10 17:44:47 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include "ft_sha256.h"
#include <libft/ft_mem.h>
#include <libft/ft_exit.h>
#include <libft/ft_prtf.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <libft/ft_str.h>

void	sha256_str(t_global *g, void *str)
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
		sha256_chunk(g, &s[idx]);
		idx += 64;
	}
	if (!len || idx != len)
	{
		ft_memcpy(buf, &s[idx], len % 64);
		sha256_pad_n_proc_c(g, buf, len % 64, len);
		sha256_print(g, 2, str);
		return;
	}
}

void	sha256_file(t_global *g, const char *fname)
{
	int		fd;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "Could not open %s (%s)\n", fname, strerror(errno));
		return;
	}
	sha256_fd(g, fd, fname);
	ft_assert(close(fd) == 0, "Could not close file (%s)", fname);
}

void	sha256_stdin(t_global *g, void *fuck_c)
{
	sha256_fd(g, STDIN_FILENO, fuck_c);
}
