/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:42:56 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/05 21:11:49 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MAX 9223372036854775807

static int	check(unsigned long long a, int s, char c)
{
	if ((a > MAX / 10 || (a == MAX / 10 && c - '0' > 7)) && s == 1)
		return (-1);
	else if ((a > MAX / 10 || (a == MAX / 10 && c - '0' > 8)) && s == -1)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	result;
	int					sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] != '\0' && (str[i] >= 9 && str[i] <= 13)) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check(result, sign, str[i]) != 1)
			return (check(result, sign, str[i]));
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
