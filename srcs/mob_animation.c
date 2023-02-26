#include "../includes/so_long.h"

void mobs_delete_and_put_images(t_map *map, xpm_t **xpm, size_t mob_num, size_t x_mob, size_t y_mob, t_img new_image)
{
	mlx_delete_image(map->mlx, map->mob.mob_img[mob_num]);
	//printf("mob_num %ld\n", mob_num); // debug
	//printf("mob_num %d\n", new_image); // debug
	//printf("mob_num %d\n", new_image); // debug
	map->mob.mob_img[mob_num] = mlx_texture_to_image(map->mlx, &xpm[new_image]->texture);
	mlx_image_to_window(map->mlx, map->mob.mob_img[mob_num], x_mob, y_mob);
}

void check_damage(t_map *map, size_t x_char, size_t y_char, size_t mob_num)
{
	size_t x_mob = ((map->mob.type[0])[mob_num]->instances[0].x) / BLOCK;
	size_t y_mob = ((map->mob.type[0])[mob_num]->instances[0].y) / BLOCK;

	if (x_char == x_mob && y_char == y_mob)
	{
		map->lives--;
		printf("%d\n", map->lives); // debug
	}
}

static void mob_moves(t_map *map, t_mob *mob, size_t mob_num)
{	
	if ((mob->x_mob[mob_num] - BLOCK >= 0 + BLOCK) && map->mob_move_left[mob_num] == true) 
	// there is no wall on the left
	{
		if (map->mob_dir[mob_num] == WITCH_L_DOWN)
			map->mob_dir[mob_num] = WITCH_L_UP;
		else
			map->mob_dir[mob_num] = WITCH_L_DOWN;

		(map->mob.type[0])[mob_num]->instances[0].x -= BLOCK;

		if (mob->x_mob[mob_num] - BLOCK == 0 + BLOCK)
			map->mob_move_left[mob_num] = false;
	}
	
	else if ((mob->x_mob[mob_num] + BLOCK <= (map->width * BLOCK) - BLOCK * 2) && map->mob_move_left[mob_num] == false) 
	// there is no wall on the right
	{	
		if (map->mob_dir[mob_num] == WITCH_R_DOWN)
			map->mob_dir[mob_num] = WITCH_R_UP;
		else
			map->mob_dir[mob_num] = WITCH_R_DOWN;
		
		(map->mob.type[0])[mob_num]->instances[0].x += BLOCK;

		if (mob->x_mob[mob_num] + BLOCK == (map->width * BLOCK) - BLOCK * 2)
			map->mob_move_left[mob_num] = true;
	}
}

void mob_animation(t_map *map, size_t x_char, size_t y_char)
{
	static int time;
	time++;

	for (int mob_num = 0; mob_num < map->mobs; mob_num++)
	{
		if (time > 7)
		{	
			for (int mob_num = 0; mob_num < map->mobs; mob_num++)
			{
				map->mob.x_mob[mob_num] = ((map->mob.type[0])[mob_num]->instances[0].x);
				map->mob.y_mob[mob_num] = ((map->mob.type[0])[mob_num]->instances[0].y);

				mob_moves(map, &map->mob, mob_num);
				check_damage(map, x_char, y_char, mob_num);

				map->mob.x_mob[mob_num] = ((map->mob.type[0])[mob_num]->instances[0].x);
				map->mob.y_mob[mob_num] = ((map->mob.type[0])[mob_num]->instances[0].y);

				mobs_delete_and_put_images(map, map->xpm, mob_num, map->mob.x_mob[mob_num], 
					map->mob.y_mob[mob_num], map->mob_dir[mob_num]);
			}

			time = 0;
		}
	}
}