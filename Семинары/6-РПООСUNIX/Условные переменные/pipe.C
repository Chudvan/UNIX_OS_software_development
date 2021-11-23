#include <iostream>
#include <pthread.h>
#include <cstring>
#include <stdio.h>
//#include <signal.h>

#define FINISH() { 	std::cerr << (int)pthread_self() << " exits\n"; \
			pthread_mutex_unlock(&mutx); pthread_exit(0); return 0;	}

pthread_mutex_t mutx; 
pthread_cond_t condx; 
int msglen, done;
char msgbuf[256];

/* направить сообщения, посылаемые из потока чтения, на стандартное устройство вывода */ 
void* writer (void* argp ) 
{
	std::cout << "writer START" << std::endl;
	do {
		pthread_mutex_lock(&mutx); // установить взаимоисключающую блокировку 
		while (!msglen) { // цикл, если сообщения нет
			pthread_cond_wait(&condx, &mutx); // ждать условную переменную 
			std::cout << "writer HERE" << std::endl;
			if (done) FINISH(); // если выполнено, уничтожить поток
		}
		std::cout << "*> " << msgbuf << std::endl; /* направить сообщение на
		стандартное устройство вывода */
		msglen = 0; // размер буфера сообщений
		pthread_mutex_unlock(&mutx); // снять взаимоисключающую блокировку 
	} while (1);
	
	//FINISH(); // завершение и выход
}
/* читать сообщения пользователя и посылать их в поток записи */ 
void* reader (void* argp )
{
	std::cout << "reader START" << std::endl;
	do {
		pthread_mutex_lock(&mutx); //установить взаимоисключающую блокировку 
		if (!msglen) { // проверить, пуст ли буфер
			std::cout << "reader START read" << std::endl;
			if (!std::cin.getline(msgbuf, 256)) {
				std::cout << "END" << std::endl;
				break; /* получить входные данные от пользователя */
			}
			std::cout << "reader END read" << std::endl;
			//if (cin.eofO) break;
			msglen = strlen(msgbuf)+1; // установить длину сообщения
			std::cout << "send signal" << std::endl;
			pthread_cond_signal(&condx); /* дать потоку записи сигнал
			для чтения сообщения */
			std::cout << "after signal" << std::endl;
		}
		/*else {
			std::cout << "msglen: " << msglen << std::endl;
			sched_yield();
		}*/
		std::cout << "msglen: " << msglen << std::endl;
		pthread_mutex_unlock(&mutx) ; // снять взаимоисключающую блокировку 
	} while (1);
	FINISH(); // завершение и выход
}
/* главный поток для управления потоком чтения и потоком записи */ 
main () {
	pthread_t wtid, rtid;
/* инициализировать взаимоисключающую блокировку и условную переменную */
	pthread_mutex_init(&mutx, 0); 
	pthread_cond_init(&condx, 0);
/* создать поток записи */ 
	std::cout << "START " << "msglen: " << msglen << std::endl;
	if (pthread_create(&wtid, 0, writer, 0)) perror("thr_create");
/* создать поток чтения */ 
	if (pthread_create(&rtid, 0, reader, 0)) perror("thr_create"); 
/* ожидать завершения потока чтения */ 
	std::cout << "BEFORE " << "msglen: " << msglen << std::endl;
	if (!pthread_join(rtid, 0))
	{
		std::cout << "HERE" << std::endl;
		done = 1;
		pthread_cond_signal(&condx);
	}
/* удаление блокировки */
	pthread_mutex_destroy(&mutx);
	pthread_cond_destroy(&condx);
	pthread_exit(0);
	return 0;
} 
