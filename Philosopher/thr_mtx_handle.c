/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr_mtx_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalk <abalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:30:38 by abalk             #+#    #+#             */
/*   Updated: 2025/08/08 18:25:20 by abalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (EXIT_SUCCESS);
	if (22 == status && (LOCK == opcode || DESTROY == opcode
			|| UNLOCK == opcode))
		return (error_exit("The value specified by mutex is invalid"));
	else if (22 == status && INIT == opcode)
		return (error_exit("The value specified by attr is invalid."));
	else if (35 == status)
		return (error_exit("A deadlock would occur if the"
				" thread blocked waiting for mutex."));
	else if (1 == status)
		return (error_exit("The current thread does "
				"not hold a lock on mutex."));
	else if (12 == status)
		return (error_exit("The process cannot allocate "
				"enough memory to create another mutex."));
	else if (16 == status)
		return (error_exit("Mutex is locked"));
	return (error_exit("Unknown mutex error occurred"));
}

int	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		return (handle_mutex_error(pthread_mutex_lock(mutex), opcode));
	else if (UNLOCK == opcode)
		return (handle_mutex_error(pthread_mutex_unlock(mutex), opcode));
	else if (INIT == opcode)
		return (handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode));
	else if (DESTROY == opcode)
		return (handle_mutex_error(pthread_mutex_destroy(mutex), opcode));
	else
		return (error_exit("Wrong opcode for mutex handle"));
}
/* THREADS */

static int	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return (EXIT_SUCCESS);
	if (11 == status)
		return (error_exit("No resources to create another thread"));
	else if (1 == status)
		return (error_exit("The caller does not have appropriate permission\n"));
	else if (22 == status && CREATE == opcode)
		return (error_exit("The value specified by attr is invalid."));
	else if (22 == status && (JOIN == opcode || DETACH == opcode))
		return (error_exit("The value specified by thread is not joinable\n"));
	else if (3 == status)
		return (error_exit("No thread could be found corresponding to "
				"that specified by the given thread ID, thread."));
	else if (35 == status)
		return (error_exit("A deadlock was detected or the value of "
				"thread specifies the calling thread."));
	return (error_exit("Unknown thread error occurred"));
}

int	safe_thread_handle(pthread_t *thread, void *(*foo) (void *),
			void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		return (handle_thread_error(pthread_create(thread, NULL, foo, data),
				opcode));
	else if (JOIN == opcode)
		return (handle_thread_error(pthread_join(*thread, NULL), opcode));
	else if (DETACH == opcode)
		return (handle_thread_error(pthread_detach (*thread), opcode));
	else
		return (error_exit("Wrong opcode for thread_handle: "
				"use <CREATE> <JOIN> <DETACH>"));
}
//handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);