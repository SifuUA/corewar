//
// Created by Oleksiy Kres on 5/26/17.
//

#include "op.h"

void	get_lable(t_asm *begin, t_asm *head, int fd);

int 	find_lable_in_args(int *ar)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (ar[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

void	find_lable(t_asm *begin, char **args, int fd)
{
	t_asm			*save;
	int 			i;
	int 			j;
	unsigned char	*s;

	i = 0;
	j = 0;
	save = begin;
	while (save)
	{
		while (args[i])
		{
			if (ft_strcmp(save->lable, args[i]) == 0)
			{
				s = (unsigned char *)save->command;
				write(fd, s, ft_strlen(save->command));
				while (save->args[j])
				{
					if (save->l_flag[j] > 0)
						get_lable(begin, save, fd);
					else
						write(fd, save->args[j], ft_strlen(save->args[j]));
					j++;
				}
			}
			i++;
		}
		save = save->next;
	}
}

void	g_lable(t_asm *begin, t_asm *head, int fd)
{
	int 			i;
	unsigned char	*s;

	i = 0;
	if (find_lable_in_args(head->l_flag))
		find_lable(begin, head->args, fd);
	else if (head->command)
	{
		s = (unsigned char *)head->command;
		write(fd, s, ft_strlen(head->command));
		while (head->args[i])
		{
			write(fd, head->args[i], ft_strlen(head->args[i]));
			i++;
		}
	}

}

void	to_byte_code(t_asm *head)
{
	t_asm	*begin;
	char 	*file_name;
	int		fd;

	file_name = ft_strjoin(head->file_name, ".cor");
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND);
	begin = head;
	head->header = (header_t *)malloc(sizeof(header_t));
	header_parse(head, fd);
	while (head)
	{
		g_lable(begin, head, fd);
		head = head->next;
	}
}

/*int main()
{
	t_asm *assem;
	t_asm *assem1;
	t_asm *assem2;
	t_asm *assem3;
	t_asm *assem4;

	assem = (t_asm *)malloc(sizeof(t_asm));
	assem->args = (char **)malloc(sizeof(char *) * 5);
	assem1 = (t_asm *)malloc(sizeof(t_asm));
	assem1->args = (char **)malloc(sizeof(char *) * 5);
	assem2 = (t_asm *)malloc(sizeof(t_asm));
	assem2->args = (char **)malloc(sizeof(char *) * 5);
	assem3 = (t_asm *)malloc(sizeof(t_asm));
	assem3->args = (char **)malloc(sizeof(char *) * 5);
	assem4 = (t_asm *)malloc(sizeof(t_asm));
	assem4->args = (char **)malloc(sizeof(char *) * 5);

	assem->file_name = ft_strdup("NAME");
	assem->command = ft_strdup("fork");
	assem->args[0] = ft_strdup("coregeni");
	assem->l_flag[0] = 1;
	assem->next = assem1;
	assem1->command = ft_strdup("st");
	assem1->args[0] = ft_strdup("r1");
	assem1->args[1] = ft_strdup("6");
	assem1->next = assem2;
	assem2->command = ft_strdup("live");
	assem2->args[0] = ft_strdup("42");
	assem2->next = assem3;
	assem3->command = ft_strdup("fork");
	assem3->args[0] = "torpgeni";
	assem3->l_flag[0] = 1;
	assem3->next = assem4;
	assem4->lable = ft_strdup("coregeni");
	assem4->command = ft_strdup("st");
	assem4->args[0] = ft_strdup("r1");
	assem4->args[1] = ft_strdup("6");
	assem4->next = NULL;
	to_byte_code(assem);
}*/
