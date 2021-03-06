//
// Created by Yevhen Yefimov on 6/7/17.
//

#include "vm.h"

void	put_cat_on_start(t_vm	*main_struct)
{
	int i;

	i = 0;
	while (i < main_struct->players_nbr)
	{
		main_struct->players[i]->car->color = (char)(i + 1);
		main_struct->players[i]->car->pos = MEM_SIZE /
											main_struct->players_nbr * (i);
		main_struct->players[i]->car->reg[0] = (unsigned int)
				main_struct->players[i]->name;
		main_struct->players[i]->car->carry = 0;
		i++;
	}
}

void	dell_car_from_list(t_car **head, t_car *to_dell)
{
	t_car	*ptr;
	t_car	*dell;

	ptr = *head;
	if (*head == to_dell)
	{
		*head = (*head)->next;
		ft_memdel(&ptr);
	}
	else
	{
		while (ptr)
		{
			if (to_dell == ptr->next)
			{
				dell = ptr->next;
				ptr->next = ptr->next->next;
				ft_memdel(&dell);
			}
			else
				ptr = ptr->next;
		}
	}
}