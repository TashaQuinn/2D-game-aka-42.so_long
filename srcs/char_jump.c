#include "../includes/so_long.h"

void jump(t_map *map, size_t x_char, size_t y_char)
{
	size_t y_char_jump = map->img[CHAR]->instances[0].y - (BLOCK / map->accel);

	if (map->jump_lock == false)
		map->accel = ACCEL;
	else
	{
		if ((map->accel >= JUMP_HEIGHT) || (y_char_jump - BLOCK / map->accel < 0))
			map->jump_lock = false;
		else
		{
			map->img[CHAR]->instances[0].y -= BLOCK / map->accel;
			map->accel *= ACCEL_MOD;
		}
	}

	if (map->map[y_char + 1][x_char + 1] != '1')
		map->img[CHAR]->instances[0].y += 3;
	else if (mlx_is_key_down(map->mlx, MLX_KEY_W) && map->map[y_char - 1][x_char] != '1' 
			&& map->map[y_char + 1][x_char] == '1')
		map->jump_lock = true;
}
