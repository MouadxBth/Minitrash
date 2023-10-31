/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:31:47 by eamrati           #+#    #+#             */
/*   Updated: 2023/10/31 16:53:45 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdlib.h>

void ack(pid_t pid)
{
	kill(pid, SIGUSR1);
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static int		count;
	static char		res [4];
	static int		cycle;
	static pid_t	pid;

	if (pid == 0)
		pid = info->si_pid;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		ft_memset(&res, 0, 4);
		count = 0;
	}
	(void) info;
	(void) ucontext;
	if (sig == SIGUSR2)
		res[cycle] |= (0x01 << count);
	count += 1;
	if (count == 8)
		cycle++;
	if (count == 8*4)
	{
		write(1, res, 4);
		if (res[0] == 0 && res[1] == 1 && res[2] == 0 && res[3] == 0)
			ack(pid);
		ft_memset(&res, 0, 4);
		count = 0;
		cycle = 0;
	}
}

int	main(void)
{
	struct sigaction	info;

	ft_memset(&info, 0, sizeof(struct sigaction));
	info.__sigaction_u.__sa_sigaction = handler;
	info.sa_flags = SA_SIGINFO;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &info, NULL);
	sigaction(SIGUSR2, &info, NULL);
	while (1)
		pause();
	return (0);
}
