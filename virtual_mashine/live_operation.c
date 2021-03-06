//
// Created by Yevhen Yefimov on 5/27/17.
//

#include "vm.h"

int		get_int_from_byte_code(char *byte_array)
{
	int		i;

	i = ((byte_array[0] & 0xFF) << 24) + ((byte_array[1] & 0xFF) << 16)
			+ ((byte_array[2] & 0xFF) << 8) + (byte_array[3] & 0xFF);
	return (i);
}

void    get_live_func(char *map, t_car *car)
{
    if (!(car->data = ft_memdup(5, map, car->pos + 1)))
		ft_error(ft_strjoin(ERR_MEM_ALLOC, "file: live_operation.c:17"));
	car->op_tabble.nb_tours = car->op_tabble.nb_tours - 1;

    //printf ("-> read LIVE instruction, data = %s\n", car->data); //printf
}

int		check_who_live(unsigned int number, t_vm *main_struct)
{
	int			i;

	i = 0;
	while (main_struct->players[i])
	{
		if (number == main_struct->players[i]->name)
		{
			main_struct->players[i]->lives_in_current_period++;
			return (main_struct->players[i]->name);
		}
		i++;
	}
	return (0);
}

void    do_live_func(t_vm *main_struct, t_car *car)
{
	unsigned int number;

	main_struct->nbr_of_lifes++;
	main_struct->count_live_functions++;
	car->live = 1;
	number = (unsigned int)get_int_from_byte_code(car->data);
	main_struct->last_live[0] = check_who_live(number, main_struct);
	//if (main_struct->last_live[0] != 0)
	//	ft_printf ("Player ->%d<- is ALIVE\n", main_struct->last_live[0]);
	main_struct->last_live[1] = main_struct->cycle + 1;
	car->pos = car->pos + DIR_SIZE + 1;
    car->op_tabble.opcode = 0;
    ft_strdel(&(car->data));
}

