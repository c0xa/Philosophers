#include "philo.h"

static int checkError(int num_argv, char **argv)
{
	int num = ft_atoi(argv[num_argv]);
	printf("num = %d\n", num);
	if (num < 1) {
		printf("Wrong arguments %d\n", num_argv);
		return -1;
	}
	return num;
}

static int parser(t_philo *philo, int argc, char **argv) 
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
			philo->number_of_philosophers = digit;
		else if (num == 2)
			philo->time_to_die = digit;
		else if (num == 3)
			philo->time_to_eat = digit;
		else if (num == 4)
			philo->time_to_sleep = digit;
		else if (num == 5)
			philo->number_of_times_to_eat = digit;
		num++;
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		return 0;
	}
	t_philo	philo;
	parser(&philo, argc, argv);
	return 0;
}