/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:48:30 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/07 12:57:13 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/advent_of_code.h"

// ! DOESN'T WORK ! //

static void	increment_ascii(char **range)
{
	long int	nb;

	nb = ft_atoll(range[0]);
	free(range[0]);
	nb++;
	range[0] = ft_lltoa(nb);
}

static int	is_invalid_id(char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (len % 2 != 0)
	return (0);
	if (len == 2)
		return (id[0] == id[1]);
	if (ft_strncmp(id, id + (len / 2), len / 2) == 0)
		return (1);
	return (0);
}

int	main(void)
{
	char					*ranges_line;
	char					**ranges;
	char					**range;
	int						file_desc;
	int						index;
	unsigned long long int	comb;

	file_desc = open("ranges", O_RDONLY);
	if (file_desc == -1)
		return (1);
	ranges_line = get_next_line(file_desc);
	close(file_desc);
	ranges = ft_split(ranges_line, ',');
	free(ranges_line);
	comb = 0;
	index = 1;
	while (*ranges)
	{
		range = ft_split(*ranges, '-');
		while (1)
		{
			if (is_invalid_id(range[0]))
			{
				comb += ft_atol(range[0]);
				ft_printf("%i		%llu \n\n", index, comb);
			}
			if (ft_strncmp(range[0], range[1], ft_strlen(range[1])) == 0)
				break ;
			increment_ascii(range);
		}
		free(range[1]);
		free(range);
		free(*ranges);
		index++;
		ranges++;
	}
	free(ranges - index);
	return (0);
}
