/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:53:55 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/09 15:19:04 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <libft/ft_prtf.h>

// int main_md5(char *s[]){ft_printf("main md5\n"); return 0;}
int main_sha256(char *s[]){(void)s; ft_printf("main sha256\n"); return 0;}

int main(int argc, char *argv[])
{
	t_subcmd	*command;

	(void)argc;
	command = get_subcmd(argv[1]);
	if (command)
		command(&argv[2]);
}
