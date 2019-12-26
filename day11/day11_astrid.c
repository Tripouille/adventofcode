#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define BASE 0
#define WHITE 1
#define BLACK 2
#define COLOR 0
#define DIRECTION 1

typedef struct  s_pos
{
    int         x;
    int         y;
}               t_pos;

enum    {NORTH, EAST, SOUTH, WEST};

long	values[1000000];
char	b[100000];
long	relative_base;
char    map[10000][10000] = {0};
t_pos   position;
char    output_status;
int     count;
int     direction;

void    paint(t_pos *position, int value)
{
    if (map[position->x][position->y] == BASE)
        count++;
    map[position->x][position->y] = value ? WHITE : BLACK;
    output_status = DIRECTION;
}

void    move(t_pos *position, int value)
{
    if (value == 0)
        direction = direction == WEST ? NORTH : direction + 1;
    else
        direction = direction == NORTH ? WEST : direction - 1;
    if (direction == NORTH)
        (position->y)--;
    else if (direction == EAST)
        (position->x)++;
    else if (direction == SOUTH)
        (position->y)++;
    else if (direction == WEST)
        (position->x)--;
    output_status = COLOR;
}

long	*get_addr(int param_mode, int param_pos)
{
	if (param_mode == 0)
		return (values + values[param_pos]);
	if (param_mode == 1)
		return (values + param_pos);
	if (param_mode == 2)
		return (values + values[param_pos] + relative_base);
	return (0);
}

void	launch_computer(t_pos *position)
{
	long		i;
	long		*value1;
	long		*value2;
	long		*value3;

	i = 0;
	while (values[i] != 99)
	{
		value1 = get_addr((values[i] / 100) % 10, i + 1);
		value2 = get_addr((values[i] / 1000) % 10, i + 2);
		value3 = get_addr((values[i] / 10000) % 10, i + 3);
		if (values[i] % 100 == 1)
		{
			*value3 = *value1 + *value2;
			i += 4;
		}
		else if (values[i] % 100 == 2)
		{
			*value3 = *value1 * *value2;
			i += 4;
		}
		else if (values[i] % 100 == 3)
		{
            *value1 = map[position->x][position->y] == WHITE ? 1 : 0;
			i += 2;
		}
		else if (values[i] % 100 == 4)
		{
            if (output_status == COLOR)
                paint(position, *value1);
            else
                move(position, *value1);
			i += 2;
		}
		else if (values[i] % 100 == 5)
		{
			if (*value1)
				i = *value2;
			else
				i += 3;
		}
		else if (values[i] % 100 == 6)
		{
			if (!*value1)
				i = *value2;
			else
				i += 3;
		}
		else if (values[i] % 100 == 7)
		{
			if (*value1 < *value2)
				*value3 = 1;
			else
				*value3 = 0;
			i += 4;
		}
		else if (values[i] % 100 == 8)
		{
			if (*value1 == *value2)
				*value3 = 1;
			else
				*value3 = 0;
			i += 4;
		}
		else if (values[i] % 100 == 9)
		{
			relative_base += *value1;
			i += 2;
		}
	}
}

#define WIDTH 50

void    print_result(void)
{
    int     x;
    int     y;
    
    y = 4999 - WIDTH;
    while (++y < 4999 + WIDTH)
    {
        x = 4999 + WIDTH;
        while (--x > 4999 - WIDTH)
            printf("%c", map[x][y] == WHITE ? 'O' : ' ');
        printf("\n");
    }
}

int		main(int ac, char **av)
{
	char			*buffer = b;
	long			i;
	int				fd;
    t_pos           position;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	read(fd, b, 100000);
	i = 0;
	while (*buffer != '\n')
	{
		values[i++] = atol(buffer);
		while (isdigit(*buffer) || *buffer == '-')
			buffer++;
		if (*buffer == ',')
			buffer++;
	}
	relative_base = 0;
	position.x = 4999;
	position.y = 4999;
    map[position.x][position.y] = WHITE;
    output_status = COLOR;
    count = 0;
    direction = NORTH;
	launch_computer(&position);
    //printf("result = %d\n", count);
    print_result();
	return(0);
}
