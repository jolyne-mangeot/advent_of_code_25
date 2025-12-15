/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:48:30 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/15 19:11:26 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/advent_of_code.h"

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

static int	divide_id(size_t id, size_t len, size_t divider)
{
	size_t	*values;
	size_t	temp;
	int		result;

	values = (size_t *)malloc(sizeof(size_t) * (len / divider));
	temp = 0;
	while (temp < (len / divider))
	{
		values[temp] = id
			/ get_tens_power(len - (divider * (temp + 1)));
		if (temp)
			values[temp] %= get_tens_power(divider);
		temp++;
	}
	temp = 0;
	result = 1;
	while (temp < (len / divider) - 1)
	{
		if (values[temp] != values[temp + 1])
			result = 0;
		if (!result)
			break ;
		temp++;
	}
	free(values);
	return (result);
}

static int	is_invalid_id(size_t id)
{
	size_t	temp;
	size_t	len;
	int		result;

	len = 1;
	temp = id;
	while (temp >= 10)
	{
		temp /= 10;
		len++;
	}
	temp = 1;
	result = 0;
	while (temp < len)
	{
		if (len % temp == 0)
			result = divide_id(id, len, temp);
		if (result)
		{
			ft_printf("divider : %lld, id : %lld\n", temp, id);
			return(result);
		}
		temp++;
	}
	return (result);
}

static size_t	browse_range(size_t id, size_t maximum)
{
	size_t	count;

	count = 0;
	while (id <= maximum)
	{
		if (is_invalid_id(id))
			count += id;
		id++;
	}
	return (count);
}

static size_t	browse_ranges(char **ranges)
{
	char	**range;
	size_t	count;
	size_t	index;

	count = 0;
	index = 0;
	while (ranges[index])
	{
		range = ft_split(ranges[index], '-');
		ft_printf("\n\n***\n%d\n***\n\n", index);
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
