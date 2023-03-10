#include "../includes/so_long.h"

bool image_to_window(t_map *map, int y_height, int x_width)
{
    //return (free_array(map->img, "Image display has failed!", map), false);

	static int i = 0; // used for iterating the mobs

	/*-----------------------------------------------------------------------------------------------------------------------------------------*/
	if (map->map[y_height][x_width] == '1')
	{
		if (x_width == 0 || y_height == 0 || y_height == map->height - 1 || x_width == map->width - 1) // boarders (/walls)
		{
			if ((mlx_image_to_window(map->mlx, map->img[WALL], x_width * BLOCK, y_height * BLOCK)) == -1)
				return (ft_putendl_fd("Image display has failed!", STDOUT_FILENO), false);
		}
		else // loading tiles that are inside the boarders
		{
			if (map->tiles % 2 == 0) // only for even tiles cuz the size of the cloud is two blocks, but we can load it only on one block
			{
				if (mlx_image_to_window(map->mlx, map->tile.tile_img[map->tiles], x_width * BLOCK, y_height * BLOCK) == -1)
					return (ft_putendl_fd("Image display has failed!", STDOUT_FILENO), false);
				
				mlx_set_instance_depth(&map->tile.tile_img[map->tiles]->instances[0], -400); // avoid blocking main char
			}
			else // thus we hide the second block
			{
				if (mlx_image_to_window(map->mlx, map->tile.tile_img[map->tiles], x_width * BLOCK, y_height * BLOCK) == -1)
					return (ft_putendl_fd("Image display has failed!", STDOUT_FILENO), false);
					
				mlx_set_instance_depth(&map->tile.tile_img[map->tiles]->instances[0], -600); // hiding odd tiles below the bg (which is at -500)
			}

			map->tile.x_tile[map->tiles] = ((map->tile.type[0])[map->tiles]->instances[0].x);
			map->tile.y_tile[map->tiles] = ((map->tile.type[0])[map->tiles]->instances[0].y);
			map->tile.x_tile_start[map->tiles] = ((map->tile.type[0])[map->tiles]->instances[0].x - BLOCK * 2);
			map->tile.y_tile_start[map->tiles] = ((map->tile.type[0])[map->tiles]->instances[0].y - BLOCK * 2);
			map->tile.x_tile_end[map->tiles] = ((map->tile.type[0])[map->tiles]->instances[0].x + BLOCK * 2);
			map->tile.y_tile_end[map->tiles] = ((map->tile.type[0])[map->tiles]->instances[0].y + BLOCK * 2);
			map->tile_hidden[map->tiles] = false;

			map->tiles++;
		}
	}
	/*-----------------------------------------------------------------------------------------------------------------------------------------*/
	else if (map->map[y_height][x_width] == 'P')
	{
		if ((mlx_image_to_window(map->mlx, map->img[CHAR], x_width * BLOCK, y_height * BLOCK)) == -1)
            return (ft_putendl_fd("Image display has failed!", STDOUT_FILENO), false);
    }
	/*-----------------------------------------------------------------------------------------------------------------------------------------*/
	else if (map->map[y_height][x_width] == 'E') 
	{
		if ((mlx_image_to_window(map->mlx, map->img[DOOR], x_width * BLOCK, y_height * BLOCK)) == -1)
            return (ft_putendl_fd("Image display has failed!", STDOUT_FILENO), false);

		map->door.x_door_start = (map->img[DOOR]->instances[0].x / BLOCK);
		map->door.y_door_end = (map->img[DOOR]->instances[0].y / BLOCK);
    }
	/*-----------------------------------------------------------------------------------------------------------------------------------------*/
	else if (map->map[y_height][x_width] == 'C') 
	{
		if(((mlx_image_to_window(map->mlx, map->star.star_img[map->stars], x_width * BLOCK, y_height * BLOCK)) == -1))
            return (ft_putendl_fd("Image display has failed!", STDOUT_FILENO), false);	

		map->star.x_star[map->stars] = (map->star.type[0])[map->stars]->instances[0].x;
		map->star.y_star[map->stars] = (map->star.type[0])[map->stars]->instances[0].y;
		map->star.x_star_start[map->stars] = ((map->star.type[0])[map->stars]->instances[0].x - HALF_BLOCK);
		map->star.y_star_start[map->stars] = ((map->star.type[0])[map->stars]->instances[0].y - HALF_BLOCK);
		map->star.x_star_end[map->stars] = ((map->star.type[0])[map->stars]->instances[0].x + HALF_BLOCK);
		map->star.y_star_end[map->stars] = ((map->star.type[0])[map->stars]->instances[0].y + HALF_BLOCK);
		map->star_lit_up[map->stars] = false;
		mlx_set_instance_depth(&map->star.star_img[map->stars]->instances[0], -600); // hiding the stars that are not lit up

		map->stars++;
    }
	/*-----------------------------------------------------------------------------------------------------------------------------------------*/
	else if (map->map[y_height][x_width] == 'X') 
    {
		if (i == 0) // the which is 0 num
       	{
			if ((mlx_image_to_window(map->mlx, map->mob.witch_img[map->mobs], x_width * BLOCK, y_height * BLOCK)) == -1)
			{
            	return (ft_putendl_fd("Image display has failed!", STDOUT_FILENO), false);
			}

			map->mobs = -1;
		}
		else // bats are 0 and 1 nums
		{
			if ((mlx_image_to_window(map->mlx, map->mob.bat_img[map->mobs], x_width * BLOCK, y_height * BLOCK)) == -1)
			{
            	return (ft_putendl_fd("Image display has failed!", STDOUT_FILENO), false);
			}
		}
		
		i++;
	    map->mobs++;
    }
	/*-----------------------------------------------------------------------------------------------------------------------------------------*/
	
	return true;
}

bool display_sprites_and_lives_str(t_map *map)
{
	int y_height = -1;
	while (map->map[++y_height])
	{
		int x_width = -1;
		while (map->map[y_height][++x_width]) {
			if(!(image_to_window(map, y_height, x_width)))
				printf("%s\n", "Error occured while executing image_to_window!");
		}
	}

	if ((mlx_image_to_window(map->mlx, map->img[BG], BLOCK, BLOCK)) == -1)
        return (ft_putendl_fd("BG-to-window has failed!", STDOUT_FILENO), false);

    mlx_set_instance_depth(map->img[BG]->instances, -500); // putting it faaar away to avoid blocking the sprites

	mlx_put_string(map->mlx, "Lives:", BLOCK, HALF_BLOCK / 2);

	return true;
}

// mlx_clear_window(map->map, map->win);
