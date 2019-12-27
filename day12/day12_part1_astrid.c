#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int     get_next_line(int fd, char **line);

int     coord[4][3] = {0};
int     velocity[4][3] = {0};
int     step = 0;

void    parse_file(int fd)
{
    int     moon;
    char    *line;
    int     i;
    int     axis;
    
    moon = -1;
    while (++moon < 4)
    {
        get_next_line(fd, &line);
        i = 0;
        axis = 0;
        while (axis < 3)
        {
            while (line[i++] != '=');
            coord[moon][axis] = atoi(line + i);
            while (line[i] == '-' || (line[i] >= '0' && line[i] <= '9'))
                i++;
            axis++;
        }
    }
}

void    update_velocity(void)
{
    int     base_moon;
    int     compared_moon;
    int     axis;
    
    base_moon = 0;
    while (base_moon < 4)
    {
        compared_moon = 0;
        while (compared_moon < 4)
        {
            axis = 0;
            while (axis < 3)
            {
                if (coord[base_moon][axis] < coord[compared_moon][axis])
                    velocity[base_moon][axis]++;
                else if (coord[base_moon][axis] > coord[compared_moon][axis])
                    velocity[base_moon][axis]--;
                axis++;
            }
            compared_moon++;
            
        }
        base_moon++;
    }
}

void    update_position(void)
{
    int     moon;
    int     axis;
    
    moon = 0;
    while (moon < 4)
    {
        axis = 0;
        while (axis < 3)
        {
            coord[moon][axis] += velocity[moon][axis];
            axis++;
        }
        moon++;
    }
}

int     total_energy(void)
{
    int     total;
    int     moon;
    int     axis;
    int     potential;
    int     kinetic;
    
    total = 0;
    moon = 0;
    while (moon < 4)
    {
        potential = 0;
        kinetic = 0;
        axis = 0;
        while (axis < 3)
        {
            potential += coord[moon][axis] < 0 ? -coord[moon][axis] : coord[moon][axis];
            kinetic += velocity[moon][axis] < 0 ? -velocity[moon][axis] : velocity[moon][axis];
            axis++;
        }
        total += potential * kinetic;
        moon++;
    }
    return (total);
}

void    display_informations(void)
{
    int     moon;
    
    moon = 0;
    while (moon < 4)
    {
        printf("pos=<x=%d, y=%d, z=%d>, vel=<x=%d, y=%d, z=%d>\n",
        coord[moon][0], coord[moon][1], coord[moon][2],
        velocity[moon][0], velocity[moon][1], velocity[moon][2]);
        moon++;
    }
}

int		main(int ac, char **av)
{
	int				fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
    parse_file(fd);
    step = 0;
    while (step < 1000)
    {
        update_velocity();
        update_position();
        step++;
    }
    display_informations();
    printf("result = %d\n", total_energy());
	return(0);
}
