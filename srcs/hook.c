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
		gravity(map2, x_char, y_char);
		mob_animation(map2, x_char, y_char);
	}
}
