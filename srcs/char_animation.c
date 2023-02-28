#include "../includes/so_long.h"

void jump(t_map *map, size_t x_char, size_t y_char)
{
	size_t y_char_jump = map->img[CHAR]->instances[0].y - (BLOCK / map->jump_height);

	if (map->jumping == false)
		map->jump_height = JUMP_HEIGHT; // back to the default height
	else
	{
		if ((map->jump_height >= MAX_JUMP_HEIGHT) || (y_char_jump - BLOCK / map->jump_height < 0))
			// either the max height is reached or there is an obstacle above
			map->jumping = false;
		else
		{
			map->img[CHAR]->instances[0].y -= BLOCK / map->jump_height; 
			map->jump_height *= JUMP_MOD;
		}
	}

	if (map->map[y_char + 1][x_char + 1] != '1')
		map->img[CHAR]->instances[0].y += 3;
	else if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		map->jumping = true;
}

void char_delete_and_put_images(t_map *map, xpm_t **xpm, size_t x_char, size_t y_char, t_img new_image)
{
	mlx_delete_image(map->mlx, map->img[CHAR]);
	map->img[CHAR] = mlx_texture_to_image(map->mlx, &xpm[new_image]->texture);
	mlx_image_to_window(map->mlx, map->img[CHAR], x_char, y_char);
}

void move_char_up(t_map *map)
{
	int current_char_dir = map->char_dir; // for correcting the dir while flying

	if (current_char_dir == CHAR_R_FLY1)
		map->char_dir = CHAR_R_FLY2;
	else if (current_char_dir == CHAR_R_FLY2)
		map->char_dir = CHAR_R_FLY1;
	else if (current_char_dir == CHAR_L_FLY1)
		map->char_dir = CHAR_L_FLY2;
	else if (current_char_dir == CHAR_L_FLY2)
		map->char_dir = CHAR_L_FLY1;
}

void move_char_left(t_map *map)
{
	if (map->char_dir == CHAR_L_FLY1)
		map->char_dir = CHAR_L_FLY2;
	else
		map->char_dir = CHAR_L_FLY1;

	map->img[CHAR]->instances[0].x -= BLOCK / CHAR_SPEED;
}

void move_char_right(t_map *map)
{
	if (map->char_dir == CHAR_R_FLY1)
		map->char_dir = CHAR_R_FLY2;
	else
		map->char_dir = CHAR_R_FLY1;

	map->img[CHAR]->instances[0].x += BLOCK / CHAR_SPEED;
}

void char_animation(t_map *map, size_t x_char, size_t y_char)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_A) && (map->map[y_char][x_char] != '1'))
		move_char_left(map);
	else if (mlx_is_key_down(map->mlx, MLX_KEY_D) && (map->map[y_char][x_char + 2] != '1'))
		move_char_right(map);
	else if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		move_char_up(map);
	else if ((mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE) )
		|| (mlx_is_key_down(map->mlx, MLX_KEY_Q)))
		exit(0);
}
