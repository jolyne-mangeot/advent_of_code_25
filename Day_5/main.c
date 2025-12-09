/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:47:42 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/09 20:37:25 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/advent_of_code.h"

static void	setup_t_list(int fd, t_list **ranges)
{
	char	*line;
	char	**range_a;
	size_t	*range;

	while (1)
	{
		line = get_next_line(fd);
		if (*line == '\n')
			break ;
		range_a = ft_split(line, '-');
		free(line);
		range = malloc(sizeof(size_t) * 2);
		range[0] = ft_atoll(range_a[0]);
		range[1] = ft_atoll(range_a[1]);
		free(range_a[0]);
		free(range_a[1]);
		free(range_a);
		ft_lstadd_back(ranges, ft_lstnew(range));
	}
	free(line);
}

static int	is_expired(size_t id, t_list *ranges)
{
	while (ranges)
	{
		if (id >= ((size_t*)ranges->content)[0]
			&& id <= ((size_t*)ranges->content)[1])
			return (0);
		ranges = ranges->next;
	}
	return (1);
}

static int	is_overlapping(size_t range1[2], size_t range2[2])
{
	size_t r1;
	size_t r2;
	size_t r3;
	size_t r4;

	r1 = range1[0];
	r2 = range1[1];
	r3 = range2[0];
	r4 = range2[1];
	if ((r1 >= r3 && r1 <= r4) || (r2 >= r3 && r2 <= r4)
		|| (r3 >= r1 && r3 <= r2) || (r4 >= r1 && r4 <= r2))
		return (1);
	return (0);
}

static void	range_merge(t_list *ranges, t_list *t_range1, t_list *t_range2)
{
	t_list	*temp;
	size_t	*range1;
	size_t	*range2;

	range1 = (size_t *)t_range1->content;
	range2 = (size_t *)t_range2->content;
	if (range1[0] > range2[0])
		range1[0] = range2[0];
	if (range1[1] < range2[1])
		range1[1] = range2[1];
	temp = ranges;
	while (temp->next != t_range2)
		temp = temp->next;
	temp->next = temp->next->next;
	free(t_range2->content);
	free(t_range2);
}

static size_t	count_ranges(t_list *ranges)
{
	t_list	*temp;
	size_t	count;

	temp = ranges;
	count = 0;
	while (temp)
	{
		count
			+= ((size_t *)temp->content)[1] - ((size_t *)temp->content)[0] + 1;
		temp = temp->next;
	}
	return (count);
}

static size_t	browse_ranges(t_list *ranges)
{
	t_list	*temp1;
	t_list	*temp2;

	temp1 = ranges;
	while (temp1)
	{
		temp2 = temp1->next;
		while (temp2)
		{
			if (is_overlapping(temp1->content, temp2->content))
			{
				range_merge(ranges, temp1, temp2);
				browse_ranges(ranges);
				temp2 = NULL;
			}
			else
				temp2 = temp2->next;
		}
		if (temp1)
			temp1 = temp1->next;
	}
	return (count_ranges(ranges));
}

static size_t	browse_ids(int fd, t_list *ranges)
{
	char	*id_a;
	size_t	id;
	size_t	count;
	size_t	index;

	index = 0;
	count = 0;
	while (1)
	{
		id_a = get_next_line(fd);
		if (!id_a)
			break ;
		id = ft_atoll(id_a);
		free(id_a);
		index++;
		if (!is_expired(id, ranges))
			count++;
	}
	return (count);
}

// < 352986271137777

int	main(void)
{
	int		fd;
	t_list	*ranges;
	size_t	count;

	fd = open("ids", O_RDONLY);
	if (fd < 0)
		return (1);
	ranges = NULL;
	setup_t_list(fd, &ranges);
	count = browse_ranges(ranges);
	ft_printf("total fresh ids count = %lld\n", count);
	count = browse_ids(fd, ranges);
	ft_printf("current fresh ingredients count = %lld\n", count);
	close(fd);
	ft_lstclear(&ranges, &free);
	return (0);
}
