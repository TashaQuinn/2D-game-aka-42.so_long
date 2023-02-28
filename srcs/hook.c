#include "../includes/so_long.h"

void check_lives(t_map *map)
{
	int i = 0;
	size_t x_heart;

	for (int heart_num = 0; heart_num < map->lives; heart_num++)
	{	
		x_heart = HALF_BLOCK * (5 + i); 
		mlx_image_to_window(map->mlx, map->heart_img[heart_num], x_heart, BLOCK / 8);
		i += 2;
	}

	mlx_delete_image(map->mlx, map->heart_img[map->lives]);
}

void end_game(t_map *map)
{	
	int time = 0;
	
	mlx_put_string(map->mlx, "Game over!\n", map->width * BLOCK / 2 - BLOCK, map->height * BLOCK / 2 - BLOCK);

	time++;
	if (time > 100)
		exit(0);
}

void hook(void *map)
{
	t_map *const map2 = map;

	size_t x_char = (map2->img[CHAR]->instances[0].x / BLOCK);
	size_t y_char = (map2->img[CHAR]->instances[0].y / BLOCK);

	if ((((x_char == map2->door.x_door_start && y_char == map2->door.y_door_end)) 
		&& map2->lit_up_stars_count == map2->stars) || (map2->lives == 0))
		end_game(map2);
	else
	{
		jump(map2, x_char, y_char);
		char_animation(map2, x_char, y_char);
		mob_animation(map2, x_char, y_char);
		check_lives(map2);
		tile_animation(map2);
		star_animation(map2);
	
		x_char = map2->img[CHAR]->instances[0].x; // updating coords
		y_char = map2->img[CHAR]->instances[0].y;

		char_delete_and_put_images(map2, map2->xpm, x_char, y_char, map2->char_dir);
		lit_up_stars(map2, x_char, y_char);
	}
}
