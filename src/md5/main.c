/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 23:20:20 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/19 19:02:34 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "ft_md5.h"
#include <libft/ft_mem.h>

int		main_md5(int ac, char *av[])
{
	t_global	globals;

	ft_bzero(&globals, sizeof(globals));
	md5_proc_args(&globals, &av[2]);
	return (0);
}
