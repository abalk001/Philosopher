#ifndef PHILO_TOOLS_H
#define PHILO_TOOLS_H

#include "philo.h"
/* parsing*/
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
void	precise_unsleep(long usec, t_table *table);
/* monitoring */
void	monitoring(t_philo_status status, t_philo *philo);
#endif