/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:52:34 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/17 16:14:14 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/advent_of_code.h"

static char	**create_matrix(int fd, size_t mat_size[2])
{
	char	*line;
	t_list	*lst_matrix;

	line = get_next_line(fd);
	mat_size[1] = ft_strlen(line) - 1;
	lst_matrix = NULL;
	while (line)
	{
		line[mat_size[1]] = '\0';
		ft_lstadd_back(&lst_matrix, ft_lstnew(line));
		line = get_next_line(fd);
	}
	mat_size[0] = ft_lstsize(lst_matrix);
	return ((char **)ft_lstjoin(lst_matrix, 1));
}

static size_t	check_splitter(char **matrix, size_t mat_size[2],
	size_t coords[2])
{
	if (matrix[coords[0]][coords[1]] == '|')
	{
		if (matrix[coords[0] + 1][coords[1]] == '^')
		{
			if (coords[1] > 0)
				matrix[coords[0] + 2][coords[1] - 1] = '|';
			if (coords[1] < mat_size[1])
				matrix[coords[0] + 2][coords[1] + 1] = '|';
			return (1);
		}
		else
			matrix[coords[0] + 2][coords[1]] = '|';
	}
	return (0);
}

static size_t	browse_manifold(int fd)
{
	char	**matrix;
	size_t	mat_size[2];
	size_t	coords[2];
	size_t	count;

	matrix = create_matrix(fd, mat_size);
	if (!matrix)
		return (0);
	coords[1] = ft_strchr(matrix[0], 'S') - matrix[0];
	matrix[1][coords[1]] = '|';
	coords[0] = 0;
	count = 0;
	while (coords[0] < mat_size[0] - 1)
	{
		coords[1] = 0;
		while (coords[1] < mat_size[1])
		{
			count += check_splitter(matrix, mat_size, coords);
			coords[1] += 1;
		}
		coords[0] += 1;
	}
	return (count);
}

int	main(void)
{
	int		fd;
	size_t	count;

	fd = open("manifold", O_RDONLY);
	if (fd < 0)
		return (1);
	count = browse_manifold(fd);
	ft_printf("count: %llu", count);
	close(fd);
	return (0);
}
