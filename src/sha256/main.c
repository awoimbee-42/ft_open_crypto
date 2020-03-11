/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 23:20:20 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/11 18:43:23 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "ft_sha256.h"
#include <libft/ft_mem.h>

int		main_sha256(char **argv)
{
	t_global	globals;

	ft_bzero(&globals, sizeof(globals));
	sha256_proc_args(&globals, argv);
	return (0);
}
