#ifndef PHILO_H
#define PHILO_H


# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // write, usleep
# include <stdbool.h>
# include <pthread.h> // mutex and threads
# include <sys/time.h>
# include <limits.h>

/* OP CODE FOR MUTEX */

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,

}	t_opcode;

typedef enum e_time
{
	SECOND,
	MS,
	US,
}	t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_philo_status;

/* STRUCT THAT SHIT  */
typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;


//./ philo 5 800 200 200 [5]  time to die time to sleep time_fucking_dieeee
typedef struct s_philo
{
	int			id;
	long		meals_counters; // init in philo-init at 0
	bool		full; // init in philo-init
	long		last_meal_time;  // time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork; 
	pthread_t	thread_id; // a philo is a thread to societyyyy 
	t_mtx		philo_mutex; // use for monitoring and init in philo-init
	t_table		*table;
}	t_philo;


struct s_table   //shared data
{
	long	philo_nbr;  // init in parsing
	long	t_die; // init in parsing 
	long	t_eat; // init in parsing
	long	t_sleep; // init in sleep
	long	m_meals;// [4] Flag if -1 , init in parsing
	long	str_sim;
	bool	end_sim; // init in data-init
	bool	all_threads_ready; //sych philos init at fals in data-init
	long	threads_running_nbr;
	t_mtx	table_mutex; // init in data init
	t_mtx	write_mutex; // init in data init 
	pthread_t monitor_thread;
	t_fork	*fork; // array to forks 
	t_philo	*philos;
};
void	parse_input(t_table *table, char **av);
void	error_exit(const char *error);
bool	is_space(char c);
bool	is_digit(char c);
/* Data init */
void	data_init(t_table *table);
void	*safe_malloc(size_t bytes);
void	safe_thread_handle(pthread_t *thread, void *(*foo) (void *),
			void *data, t_opcode opcode);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
/* set_stuff*/
bool	sim_finish(t_table *table);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
/* Dinner */
void	dinner_start(t_table *table);
void	*dinner_simulation(void *data);
void	wait_all_threads(t_table *table);
/* time */
long	get_time(t_time_code time_code);
void	precise_unsleep(long t_to_task, t_table *table);
/* monitoring */
void	monitoring(t_philo_status status, t_philo *philo);
bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr);
void	increase_long(t_mtx *mtx, long *value);
void	*monitor_dinner(void *data);
/* CLean*/
void	clean(t_table *table);
# endif 