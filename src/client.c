/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:36:58 by hvecchio          #+#    #+#             */
/*   Updated: 2024/06/10 04:48:14 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	signal_received;

int	main(int ac, char **av)
{
	struct sigaction	s_sigaction;
	int					pid;
	int					i;
	
	s_sigaction.sa_handler = &ft_receipt_acknowledgment;
	sigaction(SIGUSR1, &s_sigaction, NULL);
	write(1, "TEST\n", 5);
	pid = ft_atoi(av[1]);
	write(1, "TEST2\n", 6);
	if (ac != 3 || pid <= 0)
		return (0);
	write(1, "TEST3\n", 6);
	i = -1;
	while (av[2][++i])
		ft_send_byte(av[2][i], 0, pid);
	write(1, "TEST4\n", 6);
	ft_send_byte(0, 0, pid);
	return (0);
}

void	ft_send_bit(int bit, int pid)
{
	int		kill_failure;
	
	write(1, "3TEST\n", 6);
	kill_failure = 0;
	signal_received = 0;
	if (bit == 1)
		kill_failure = kill(pid, SIGUSR2);
	else
		kill_failure = kill(pid, SIGUSR1);
	if (kill_failure == -1)
		exit(0);
	while (!signal_received)
	{
	}
}

void	ft_send_byte(int c, int sent_bits, int pid)
{
	sent_bits++;
	write(1, "1TEST\n", 6);
	if (sent_bits < 8)
		ft_send_byte(c / 2, sent_bits, pid);
	if (c % 2 == 1)
		ft_send_bit(1, pid);
	else
		ft_send_bit(0, pid);
}

void	ft_receipt_acknowledgment(int bit)
{
	write(1, "2TEST\n", 6);
	signal_received = 1 + bit * 0;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}