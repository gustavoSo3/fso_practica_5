#include <pthread_utils.h>
#include <stdlib.h>
#include <libsem.h>

// Macro que incluye el código de la instrucción máquina xchg
#define atomic_xchg(A,B) 	__asm__ __volatile__(	\
							"   lock xchg %1,%0 ;\n"	\
							: "=ir"  (A)			\
							: "m"  (B), "ir" (A)		\
							);

int g=0;


SEMAPHORE semaphore_get(int val)
{
	SEMAPHORE s = NULL;
	// Solicitar memoria dinámica para una struct STRSEMAPHORE usando malloc
	// Inicializar el contador del semáforo con el valor de val
	// Crear una cola (ver función queue_create()) y asignarla al apuntador de la cola en el semáforo
	
	return(s);
}

void semaphore_destroy(SEMAPHORE s)
{
	// Destruir la cola
	// Liberar la memoria del semáforo
}

void semaphore_wait(SEMAPHORE s)
{
	// Aquí debes implementar la función semaphore_wait() haciendo que el hilo que tiene que esperar
	// se bloquée de manera que no haya espera ocupada
	//	- Antes de bloquearlo hay que:
	//	-	1.- Obtener el tid del hilo (pthread_self) y guardarlo en una variable.
	//	-	2.- Guardar el tid en la cola del semáforo con queue_offer
	//	-	3.- Finalmente bloquear al hilo (block_thread)
	//			Un detalle muy importante es que antes de que el hilo se bloquée, debe liberar el atomic_xchg()
	// Recuerda quye se debe actualizar el contador del semáforo
	// Recuerda que esta función debe ejecutarse de manera atómica
}

void semaphore_signal(SEMAPHORE s)
{
	// Aquí hay que implementar la función semaphore_signal() para que un hilo que esté bloqueado en
	// el semáforo s->queue se desbloquée y se actualize el contador del semáforo-
	// Recuerda que esta función debe ejecutarse de manera atómica
	
}


