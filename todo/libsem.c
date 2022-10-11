#include <pthread_utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <libsem.h>

// Macro que incluye el código de la instrucción máquina xchg
#define atomic_xchg(A, B) __asm__ __volatile__( \
		"   lock xchg %1,%0 ;\n"                    \
		: "=ir"(A)                                  \
		: "m"(B), "ir"(A));

int g = 0;

SEMAPHORE semaphore_get(int val)
{
	// Solicitar memoria dinámica para una struct STRSEMAPHORE usando malloc
	SEMAPHORE s = malloc(sizeof(struct STRSEMAPHORE));
	// Inicializar el contador del semáforo con el valor de val
	s->count = val;
	// Crear una cola (ver función queue_create()) y asignarla al apuntador de la cola en el semáforo
	s->queue = queue_create();

	return (s);
}

void semaphore_destroy(SEMAPHORE s)
{
	// Destruir la cola
	queue_destroy(s->queue);
	// Liberar la memoria del semáforo
	free(s);
}

void semaphore_wait(SEMAPHORE s)
{
	// Aquí debes implementar la función semaphore_wait() haciendo que el hilo que tiene que esperar
	// se bloquée de manera que no haya espera ocupada
	int l = 1;
	// Recuerda que esta función debe ejecutarse de manera atómica
	do
	{
		atomic_xchg(l, g);
	} while (l != 0);

	s->count--;
	// Recuerda quye se debe actualizar el contador del semáforo
	if (s->count < 0)
	{

		//	- Antes de bloquearlo hay que:
		//	-	1.- Obtener el tid del hilo (pthread_self) y guardarlo en una variable.
		pthread_t tid = pthread_self();
		//	-	2.- Guardar el tid en la cola del semáforo con queue_offer
		queue_offer(s->queue, tid);
		//			Un detalle muy importante es que antes de que el hilo se bloquée, debe liberar el atomic_xchg()
		//	-	3.- Finalmente bloquear al hilo (block_thread)
		g = 0;
		l = 1;
		block_thread(tid);
	}
	else
	{
		g = 0;
		l = 1;
	}
}

void semaphore_signal(SEMAPHORE s)
{
	// Aquí hay que implementar la función semaphore_signal() para que un hilo que esté bloqueado en
	// el semáforo s->queue se desbloquée y se actualize el contador del semáforo-

	int l = 1;
	// Recuerda que esta función debe ejecutarse de manera atómica
	do
	{
		atomic_xchg(l, g);
	} while (l != 0);
	s->count++;
	if (s->count <= 0)
	{
		pthread_t tid_to_unlock = queue_poll(s->queue);
		unblock_thread(tid_to_unlock);
	}
	g = 0;
	l = 1;
}
