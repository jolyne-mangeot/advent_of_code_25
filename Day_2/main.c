/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:48:30 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/15 11:37:45 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/advent_of_code.h"

// ! DOESN'T WORK ! //

static size_t	get_tens_power(size_t power)
{
	size_t	ten;

	ten = 1;
	while (power >= 1)
	{
		ten *= 10;
		power--;
	}
	return (ten);
}

static int	is_invalid_id(size_t id)
{
	size_t	temp;
	size_t	*values;
	size_t	len;
	int		result;

	values = (size_t *)malloc(sizeof(size_t) * 2);
	len = 1;
	temp = id;
	while (temp >= 10)
	{
		temp /= 10;
		len++;
	}
	if (len % 2 != 0)
		return (0);
	values[0] = id / get_tens_power(len / 2);
	values[1] = id % get_tens_power(len / 2);
	result = values[0] == values[1];
	free(values);
	return (result);
}

static size_t	browse_range(size_t id, size_t maximum)
{
	size_t	count;

	count = 0;
	while (id <= maximum)
	{
		if (is_invalid_id(id))
		{
			ft_printf("%lld\n", id);
			count += id;
		}
		id++;
	}
	return (count);
}

static size_t	browse_ranges(char **ranges)
{
	char	**range;
	size_t	count;
	size_t	index;
	size_t	lens[2];

	count = 0;
	index = 0;
	while (ranges[index])
	{
		range = ft_split(ranges[index], '-');
		lens[0] = ft_strlen(range[0]);
		lens[1] = ft_strlen(range[1]);
		ft_printf("\n\n***\n%d\n***\n\n", index);
		if (lens[0] != lens[1] || lens[0] % 2 == 0)
			count += browse_range(ft_atoll(range[0]), ft_atoll(range[1]));
		free(range[0]);
		free(range[1]);
		free(range);
		free(ranges[index]);
		index++;
	}
	free(ranges);
	return (count);
}

int	main(void)
{
	char	*ranges_line;
	char	**ranges;
	int		file_desc;
	size_t	count;

	file_desc = open("ranges", O_RDONLY);
	if (file_desc == -1)
		return (1);
	ranges_line = get_next_line(file_desc);
	close(file_desc);
	ranges = ft_split(ranges_line, ',');
	free(ranges_line);
	count = browse_ranges(ranges);
	ft_printf("count : %llu", count);
	return (0);
}
