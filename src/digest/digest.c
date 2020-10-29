/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 20:03:41 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/29 16:34:07 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
#include "digest.h"
#include "main.h"


// t_digest_args parse_digest_args(char *av[])
// {
// 	t_digest_args	a;

// 	ft_bzero(&a, sizeof(a));
// 	while (*av)
// 	{
// 		if (!ft_strcmp(*av, "--"))
// 		{
// 			a.fname = av[1];
// 			if (av[1] && av[2])
// 			{
// 				ft_printf("error: extraneous argument: %s\n", av[2]);
// 				exit(1);
// 			}
// 		}
// 		else if (**av == '-')
// 		{
// 			if (ft_strcmp(&((*av)[1]), "p"))
// 				a.echo = true;
// 			if (ft_strcmp(&((*av)[1]), "q"))
// 				a.quiet = true;
// 			if (ft_strcmp(&((*av)[1]), "r"))
// 				a.rev_fmt = true;
// 			if (ft_strcmp(&((*av)[1]), "s")) // bad
// 				a.from_argv = true;
// 		}

// 		else if (!a.input)
// 		{
// 			a.input = *av;
// 		}
// 		else {
// 				ft_printf("error: Invalid Argument: %s\n", *av);
// 				exit(1);
// 		}
// 		av = &av[1];
// 	}
// 	return (a);
// }


int		digest_main(int argc, char *argv[])
{
	struct s_digest_fn_from_str		cmds[2];

	cmds[0] = (typeof(*cmds)){"md5", md5_fd};
	cmds[1] = (typeof(*cmds)){"sha256", sha256_fd};

	// void		md5_fd(const t_digest_args* args)


}
