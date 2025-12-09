/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:54:55 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/09 10:41:54 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/advent_of_code.h"

static char	**create_matrix(int fd, size_t mat_size[2])
{
	char	*line;
	t_list	*lst_matrix;

	line = get_next_line(fd);
	mat_size[0] = ft_strlen(line) - 1;
	lst_matrix = NULL;
	while (line)
	{
		line[mat_size[0]] = '\0';
		ft_lstadd_back(&lst_matrix, ft_lstnew(line));
		line = get_next_line(fd);
	}
	mat_size[1] = ft_lstsize(lst_matrix);
	return ((char **)ft_lstjoin(lst_matrix, 1));
}

static size_t	check_upper(char **matrix, size_t size[2], size_t pos[2])
{
	size_t	rolls;

	rolls = 0;
	if (pos[1] > 0)
	{
		if (pos[0] > 0 && matrix[pos[1] - 1][pos[0] - 1] == '@')
			rolls++;
		if (matrix[pos[1] - 1][pos[0]] == '@')
			rolls++;
		if (pos[0] < size[0] && matrix[pos[1] - 1][pos[0] + 1] == '@')
			rolls++;
	}
	return (rolls);
}

static size_t	check_lower(char **matrix, size_t size[2], size_t pos[2])
{
	size_t	rolls;
	char	elem;

	rolls = 0;
	if (pos[1] < size[1] - 1)
	{
		if (pos[0] > 0)
		{
			elem = matrix[pos[1] + 1][pos[0] - 1];
			if (elem == '@' || elem == 'x')
				rolls++;
		}
		elem = matrix[pos[1] + 1][pos[0]];
		if (elem == '@' || elem == '@')
			rolls++;
		if (pos[0] < size[0])
		{
			elem = matrix[pos[1] + 1][pos[0] + 1];
			if (elem == '@' || elem == '@')
				rolls++;
		}
	}
	return (rolls);
}

static size_t	check_roll(char **matrix, size_t size[2], size_t pos[2])
{
	size_t	rolls;
	char	elem;

	rolls = 0;
	rolls += check_upper(matrix, size, pos);
	if (pos[0] > 0)
	{
		elem = matrix[pos[1]][pos[0] - 1];
		if (elem == '@' || elem == 'x')
			rolls++;
	}
	if (pos[0] < size[0])
	{
		elem = matrix[pos[1]][pos[0] + 1];
		if (elem == '@' || elem == 'x')
			rolls++;
	}
	rolls += check_lower(matrix, size, pos);
	return (rolls < 4);
}

static size_t	browse_matrix(char **matrix, size_t size[2])
{
	size_t	indexes[2];
	size_t	count;

	indexes[1] = 0;
	count = 0;
	while (matrix[indexes[1]] && indexes[1] < size[1])
	{
		indexes[0] = 0;
		while (matrix[indexes[1]][indexes[0]] && indexes[0] < size[0])
		{
			if (matrix[indexes[1]][indexes[0]] == '@'
				&& check_roll(matrix, size, indexes))
			{
				count++;
				matrix[indexes[1]][indexes[0]] = 'x';
			}
			indexes[0]++;
		}
		indexes[1]++;
	}
	return (count);
}

static void	free_matrix(char **matrix)
{
	size_t	index;

	index = 0;
	while (matrix[index])
		free(matrix[index++]);
	free(matrix);
}

static void	remove_rolls(char **matrix)
{
	size_t	index;

	while (*matrix)
	{
		index = 0;
		while ((*matrix)[index])
			if ((*matrix)[index++] == 'x')
				(*matrix)[index - 1] = '.';
		matrix++;
	}
}

int	main(void)
{
	int		fd;
	char	**matrix;
	size_t	count;
	size_t	temp;
	size_t	mat_size[2];

	fd = open("rolls", O_RDONLY);
	if (fd < 0)
		return (1);
	matrix = create_matrix(fd, mat_size);
	count = 0;
	while (1)
	{
		temp = count;
		count += browse_matrix(matrix, mat_size);
		if (temp == count)
			break ;
		remove_rolls(matrix);
		ft_printf("count : %lu\n", count);
	}
	free_matrix(matrix);
	return (0);
}
