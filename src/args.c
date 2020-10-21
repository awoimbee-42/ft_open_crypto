/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:46:00 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/21 12:32:22 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <args.h>
#include <stdbool.h>
#include <libft/ft_mem.h>

t_digest_args parse_digest_args(char *av[])
{
	t_digest_args	a;

	ft_bzero(&a, sizeof(a));
	while (*av)
	{
		if (!ft_strcmp(*av, "--"))
		{
			a.input = av[1];
			if (av[1] && av[2])
			{
				ft_printf("error: extraneous argument: %s\n", av[2]);
				exit(1);
			}
		}
		else if (**av == '-')
		{
			if (ft_strcmp(&((*av)[1]), "p"))
				a.echo = true;
			if (ft_strcmp(&((*av)[1]), "q"))
				a.quiet = true;
			if (ft_strcmp(&((*av)[1]), "r"))
				a.rev_fmt = true;
			if (ft_strcmp(&((*av)[1]), "s"))
				a.str = true;
		}

		else if (!a.input)
		{
			a.input = *av;
		}
		else {
				ft_printf("error: Invalid Argument: %s\n", *av);
				exit(1);
		}
		av = &av[1];
	}
	return (a);
}
