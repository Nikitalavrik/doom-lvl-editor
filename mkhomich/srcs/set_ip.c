/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:29:31 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/10 14:29:32 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

int		calc_ip(unsigned char ad1, unsigned char ad2, unsigned char ad3,
	unsigned char ad4)
{
	int res;

	res = 0;
	res = res | ad4;
	res = (res << 8) | ad3;
	res = (res << 8) | ad2;
	res = (res << 8) | ad1;
	return (res);
}

int		find_ip(void)
{
	struct ifaddrs	*ifAddrStruct;
	struct ifaddrs	*buff;
	char			addressBuffer[INET_ADDRSTRLEN];

	getifaddrs(&ifAddrStruct);
	buff = ifAddrStruct;
	while (buff->ifa_next)
		if (ft_strcmp(buff->ifa_name, "en0") == 0 &&
			buff->ifa_addr->sa_family == AF_INET)
		{
			inet_ntop(AF_INET,
			&((struct sockaddr_in *)buff->ifa_addr)->sin_addr,
			addressBuffer, INET_ADDRSTRLEN);
			freeifaddrs(ifAddrStruct);
			return (inet_addr(addressBuffer));
		}
		else
			buff = buff->ifa_next;
	freeifaddrs(ifAddrStruct);
	return (0);
}

void	check_ip(t_doom *doom, int nb)
{
	struct sockaddr_in	buf;
	int					n;

	recvfrom(doom->soc.sock[0], &buf, sizeof(struct sockaddr_in),
	0, NULL, NULL);
	connect(doom->soc.sock[nb], (struct sockaddr *)&buf, sizeof(buf));
	buf.sin_port = htons(3333 + nb);
	send(doom->soc.sock[nb], &buf, sizeof(struct sockaddr_in), 0);
	send(doom->soc.sock[nb], &doom->max_p, sizeof(int), 0);
	send(doom->soc.sock[nb], &nb, sizeof(int), 0);
	n = 0;
	while (n < doom->max_p)
	{
		send(doom->soc.sock[nb], &n, sizeof(int), 0);
		send(doom->soc.sock[nb], &doom->play[n], sizeof(doom->play[n]), 0);
		n++;
	}
	doom->soc.addr[nb] = buf;
	connect(doom->soc.sock[nb], (struct sockaddr *)&doom->soc.addr[nb],
		sizeof(doom->soc.addr[nb]));
	printf("nb = %i ip = %x\n", nb, doom->soc.addr[nb].sin_addr.s_addr);
}
