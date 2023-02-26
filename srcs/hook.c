#include "../includes/so_long.h"

void hook(void *map)
{
	t_map *const map2 = map;

	size_t x_char = (map2->img[CHAR]->instances[0].x / BLOCK);
	size_t y_char = (map2->img[CHAR]->instances[0].y / BLOCK);

	if (((x_char == map2->door.x_door_start && y_char == map2->door.y_door_end)) 
		&& map2->lit_up_stars_count == map2->stars)
		end_game();
	else
	{
		jump(map2, x_char, y_char);
		char_animation(map2, x_char, y_char);
		mob_animation(map2, x_char, y_char);
		tile_animation(map2);
		star_animation(map2);

		x_char = map2->img[CHAR]->instances[0].x; // updating coords
		y_char = map2->img[CHAR]->instances[0].y;

		char_delete_and_put_images(map2, map2->xpm, x_char, y_char, map2->char_dir);
		lit_up_stars(map2, x_char, y_char);
	}
}
