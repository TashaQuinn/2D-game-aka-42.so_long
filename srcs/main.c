#include "../includes/so_long.h"

bool image_processing(t_map *map) {

	if(!(load_textures(map->xpm)) // mlx_load_xpm42
		|| !(convert_to_image(map, map->xpm, map->img)) // mlx_texture_to_image
		|| !(display_sprites_and_lives_str(map))) /* parse 1PECX chars + assign sprites' 
			coords (image_to_window), display sprites ans "lives: " string */
		return false;

	return true;
}

int	main(int argc, char **argv)
{
	(void)argc;
	
	t_map *map = map_parsing(argc, argv);
	image_processing(map); // load, convert and display imgs
	mlx_loop_hook(map->mlx, &hook, map); // make everybody move, move!
	mlx_loop(map->mlx);

	return 0;
}

void terminate(t_map *map) 
{
	//kill(map->pid, SIGKILL);
	mlx_close_window(map->mlx);
	mlx_terminate(map->mlx);
	close_window(map, "Oups!");

	exit(0);
}

void close_window(t_map *map, char *str)
{
	ft_putendl_fd("Error\n", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);

	terminate(map);
}
