/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 23:20:20 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/10 17:45:26 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "ft_md5.h"
#include <libft/ft_mem.h>

int		main_md5(char **argv)
{
	t_global	globals;

	ft_bzero(&globals, sizeof(globals));
	md5_proc_args(&globals, argv);
	return 0;
}

