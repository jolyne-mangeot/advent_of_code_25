/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:19:55 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/06 17:00:20 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static int	high_value_index(char *bank, int len)
{
	int	highest_value;
	int	index;

	if (bank)
		highest_value = 0;
	else
		return (0);
	index = 0;
	while (bank[index] && index < len)
	{
		if (bank[index++] > bank[highest_value])
			highest_value = index - 1;
	}
	return (highest_value);
}

int	main(void)
{
	size_t	count;
	size_t	bank_len;
	char	*bank;
	char	voltage[3];
	size_t	index;
	int		fd;

	fd = open("voltages", O_RDONLY);
	if (fd < 0)
		return (1);
	voltage[2] = '\0';
	count = 0;
	while (1)
	{
		bank = get_next_line(fd);
		if (!bank)
			break ;
		bank_len = ft_strlen(bank) - 1;
		index = high_value_index(bank, bank_len);
		ft_printf("highest value : %c\n", bank[index]);
		if (index == bank_len - 1)
		{
			voltage[0] = bank[high_value_index(bank, index)];
			voltage[1] = bank[index];
		}
		else
		{
			voltage[0] = bank[index];
			voltage[1] = bank[high_value_index(
				bank + index + 1, bank_len - index) + index + 1];
		}
		ft_printf("voltage : %d\n", ft_atoi(voltage));
		count += ft_atoi(voltage);
		free(bank);
	}
	printf("%lu", count);
	return (0);
}
