/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:55:32 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/09 16:33:38 by awoimbee         ###   ########.fr       */
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

void	md5_file(char *fname)
{
	int		fd;

	fd = open(fname, O_RDONLY);
	ft_assert(fd > 0, "Could not open %s (%s)\n", fname, strerror(errno));
	md5_fd(fd);
}

void	md5_stdin()
{
	md5_fd(STDIN_FILENO);
}

void	md5_fd(int filedesc)
{
	char	input[64];
	ssize_t	nb;
	size_t	input_size;
	int		one_not_written;

	input_size = 0;
	one_not_written = 1;
	while (1)
	{
		nb = read(filedesc, input, 64);
		input_size += nb;
		if (nb != 64)
			break;
		md5_chunk(input);
	}
	ft_assert(nb != -1, "Could not read from file descriptor");
	if (nb >= 55) { // 56??
		one_not_written = 0;
		ft_bzero(&input[nb], 64 - nb);
		input[nb] |= 1 << 7;
		md5_chunk(input);
		nb = 0;
	}
	// parse last 448 bits + the 64bits filesize

	ft_bzero(&input[nb], 64 - 8 - nb); // no need to bzero last 64 bits
	input[nb] |= one_not_written ? 1 << 7 : 0;
	// ft_memcpy(&input[63-8], &input_size, 8);
	*((uint64_t*)&input[63 - 8]) = (uint64_t)input_size;
	md5_chunk(input);

	char *s = md5_get_digest();
	ft_printf("%s\n", s);
	free(s);
}
