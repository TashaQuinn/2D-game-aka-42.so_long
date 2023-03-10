#include "../includes/so_long.h"

t_map *init_map(char *line)
{
	t_map *map = malloc(sizeof(t_map));
	if (!map)
		return NULL;

	map->map = ft_split(line, '\n');

	int i = 0;
	while (map->map[i])
		i++;

	map->width = ft_strlen(map->map[0]);
	map->height = i;
	map->mlx = mlx_init(map->width * BLOCK, map->height * BLOCK, "Some Starry Night", true);
	map->stars = 0;
	map->lit_up_stars_count = 0;
	map->mobs = 0; 
	map->char_dir = CHAR_R_FLY1;
	map->lives = LIVES;
	map->tiles = 0;
	map->jump_height = JUMP_HEIGHT;
	for (int bat_num = 0; bat_num < BATS_COUNT; bat_num++)
	{
		if (bat_num % 2 == 0)
			map->bat_move_left[bat_num] = false;
		else
			map->bat_move_left[bat_num] = true;
	}

	free(line);

	return map;
}

char *get_line(char **av)
{
	int fd = open(av[1], O_RDONLY);
	//if (fd == -1)
		//error_fd();

	char *new_line = ft_strdup("");
	char *tmp;

	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break ;
		tmp = new_line;
		new_line = ft_gnl_strjoin(new_line, line);
		free(tmp);
		free(line);
	}

	close(fd);

	return new_line;
}

t_map *map_parsing(int argc, char **argv)
{
	(void)argc;

	char *line = get_line(argv);
	t_map *map = init_map(line);

	return map;
}