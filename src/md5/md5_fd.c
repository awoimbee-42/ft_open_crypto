/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:55:32 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/07 18:49:47 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_md5.h"
#include <libft/ft_nb.h>
#include <libft/ft_mem.h>

void	md5_fd(int filedesc)
{
	char	input[512];
	ssize_t	nb;
	size_t	input_size;
	int		one_not_written;

	one_not_written = 1;
	while (1)
	{
		nb = read(filedesc, input, 512);
		input_size += nb;
		if (nb != 512)
			break;
		md5_chunk(input);
	}
	if (nb == -1)
	{
		exit(EXIT_FAILURE);
		// handle
	}
	if (nb >= 447) {
		input[nb++] = 1;
		one_not_written = 0;
		ft_bzero(&input[nb], 512 - nb);
		md5_chunk(input);
		nb = 0;
	}
	// parse last 448 bits + the 64bits filesize
	input[nb++] = one_not_written;
	ft_bzero(&input[nb], 512 - 64 - nb); // no need to bzero last 64 bits
	ft_memcpy(&input[512 - 64], input_size, 64);
	md5_chunk(input);

	printf("%s\n", md5_get_digest());
}
