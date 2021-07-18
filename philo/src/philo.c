#include "philo.h"

static int checkError(int num_argv, char **argv)
{
	int num = ft_atoi(argv[num_argv]);
	if (num < 1 || num > MAXPHILO) {
		printf("Wrong arguments %d, value = %s\n", num_argv, argv[num_argv]);
		return -1;
	}
	return num;
}

static int parser(t_value *value, int argc, char **argv) 
{
	int num;
	int digit;

	num = 1;
	digit = 0;
	while (--argc > 0)
	{
		digit = checkError(num, argv);
		if (digit == -1)
			return (-1);
		if (num == 1)
			value->number_of_philosophers = digit;
		else if (num == 2)
			value->time_to_die = digit;
		else if (num == 3)
			value->time_to_eat = digit;
		else if (num == 4)
			value->time_to_sleep = digit;
		else if (num == 5)
			value->number_of_times_to_eat = digit;
		num++;
	}
	return 0;
}


int main(int argc, char **argv) {
	t_value	value;
	t_data data;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		return 0;
	}	
	if (parser(&value, argc, argv) == -1)
		return (0);
	data.value = &value;
	if (initial_main(&data) == -1)
		return (0);
	return 0;
}