/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:20:19 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/16 17:24:53 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/advent_of_code.h"

static size_t	make_s_array(char **values_a, t_list **values)
{
	char	**temp;
	size_t	index;
	size_t	count;
	size_t	*array;

	if (!values_a)
		return (0);
	count = 0;
	temp = values_a;
	while (*temp++)
		count++;
	array = (size_t *)malloc((sizeof(size_t) * count));
	index = 0;
	while (index < count)
	{
		array[index] = ft_atoll(values_a[index]);
		free(values_a[index++]);
	}
	free(values_a);
	ft_lstadd_back(values, ft_lstnew(array));
	return (count);
}

static size_t	make_values_list(int fd, t_list **values)
{
	size_t	values_index;
	size_t	index;
	char	*line;
	char	**operation;
	char	*sign;

	*values = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (*line == '*' || *line == '+')
			break;
		values_index = make_s_array(ft_split(line, ' '), values);
		free(line);
	}
	operation = ft_split(line, ' ');
	sign = (char *)malloc(sizeof(char) * (values_index + 1));
	index = 0;
	while (*operation)
	{
		sign[index++] = **operation;
		operation++;
	}
	ft_lstadd_front(values, ft_lstnew(sign));
	return (values_index);
}

static size_t	make_operation(t_list *values, size_t index)
{
	char	sign;
	size_t	result;

	sign = ((char *)values->content)[index];
	values = values->next;
	result = ((size_t *)values->content)[index];
	values = values->next;
	if (sign == '+')
	{
		while (values)
		{
			result += ((size_t *)values->content)[index];
			values = values->next;
		}
	}
	else if (sign == '*')
	{
		while (values)
		{
			result *= ((size_t *)values->content)[index];
			values = values->next;
		}
	}
	return (result);
}

static size_t	browse_worksheet(int fd)
{
	t_list	*values;
	size_t	values_index;
	size_t	index;
	size_t	result;

	values = NULL;
	values_index = make_values_list(fd, &values);
	index = 0;
	result = 0;
	while (index < values_index)
	{
		result += make_operation(values, index);
		index++;
	}
	ft_lstclear(&values, &free);
	return (result);
}

int	main(void)
{
	int		fd;
	size_t	result;

	fd = open("worksheet", O_RDONLY);
	if (fd < 0)
		return (1);
	result = browse_worksheet(fd);
	ft_printf("%llu", result);
	close(fd);
	return (0);
}
