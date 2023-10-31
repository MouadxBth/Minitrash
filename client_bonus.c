/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:31:04 by eamrati           #+#    #+#             */
/*   Updated: 2023/10/31 16:00:06 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>

void recv(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Signal received!");
	exit(0);
}

void	send(int pid, char *buffer)
{	
	int		a;
	int		inner;
	char	c;

	a = 0;
	while (buffer)
	{
		c = buffer[a];
		inner = 0;
		while (inner < 8)
		{
			if (c & 0x01)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(500);
			c >>= 1;
			inner++;
		}
		if (buffer[a] == 0)
			while (1)
				pause();
		a++;
	}
}

static t_bool	isnumber(char *arg1)
{
	while (arg1 && *arg1 && (*arg1 == ' ' || *arg1 == '\n'
			|| *arg1 == '\t' || *arg1 == '\v'
			|| *arg1 == '\f' || *arg1 == '\r'))
		arg1++;
	if (*arg1 == '-' || *arg1 == '+')
		arg1++;
	if (*arg1 == 0 || !(*arg1 >= '0' && *arg1 <= '9'))
		return (FALSE);
	while (*arg1 >= '0' && *arg1 <= '9')
		arg1++;
	while (arg1 && *arg1 && (*arg1 == ' ' || *arg1 == '\n'
			|| *arg1 == '\t' || *arg1 == '\v'
			|| *arg1 == '\f' || *arg1 == '\r'))
		arg1++;
	if (*arg1)
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	struct sigaction	info;
	
	info.__sigaction_u.__sa_handler = recv;
	sigaction(SIGUSR1, &info, NULL);
	if (argc != 3)
	{		
		ft_printf("You need to enter 2 arguments only\n");
		return (1);
	}
	if (!isnumber(argv[1]))
	{
		ft_printf("pid is not a number");
		return (1);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		ft_printf("Don't ruin the session!\n");
		return (1);
	}
	send(ft_atoi(argv[1]), argv[2]);
	return (0);
}
