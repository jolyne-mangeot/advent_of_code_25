/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:19:55 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/07 12:56:57 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/advent_of_code.h"

static int	high_value_index(char *bank, int len)
{
	int	highest_value;
	int	index;

	if (bank)
		highest_value = 0;
	else
		return (0);
	index = 0;
	while (bank[index] && index <= len)
	{
		if (bank[index++] > bank[highest_value])
			highest_value = index - 1;
	}
	return (highest_value);
}

static void	recursive_batt(char *bank, char *voltage,
	size_t index, int batt_pos)
{
	size_t	bank_len;
	size_t	bat_index;

	bank_len = ft_strlen(bank) - 1;
	bat_index = high_value_index(bank + index, bank_len - batt_pos - index)
		+ index;
	voltage[12 - batt_pos] = bank[bat_index];
	if (batt_pos > 1)
		recursive_batt(bank, voltage, bat_index + 1, batt_pos - 1);
}

int	main(void)
{
	long long int	count;
	char			voltage[13];
	char			*bank;
	int				fd;
	int				index;

	fd = open("voltages", O_RDONLY);
	if (fd < 0)
		return (1);
	ft_bzero(voltage, 12);
	count = 0;
	index = 1;
	while (1)
	{
		bank = get_next_line(fd);
		if (!bank)
			break ;
		recursive_batt(bank, voltage, 0, 12);
		ft_printf("bank %d : %llu\n", index, ft_atoll(voltage));
		count += ft_atoll(voltage);
		index++;
		free(bank);
	}
	ft_printf("\n\nvoltage : %llu\n", count);
	return (0);
}
