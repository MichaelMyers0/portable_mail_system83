#include <fcntl.h>
#include "sock_lib.h"
#include "search.h"
#include "stack.h"
enum {alarm_t = 5};
enum {num_of_clients_to_handle = 2};
enum {sleep_t = 2};
static void clean_buf(buf)
char* buf;
{
	int i, len;
	len = strlen(buf);
	for (i = 0; i < len; i++)
		*(buf + len) = 0;
}
main()
{
	int iter_sfd, fd, counter, client_num;
	const char* path = "iterative_server_socket";
	struct sockaddr_un sun;
	char datagram[datagram_cap], ppath[datagram_cap];
	size_t len;
	socklen_t slen;
	struct stack s;

	counter = 0;
	client_num = 0;

	init(&s);
	push(&s, ".");
	change_signal_disposition();

	sun.sun_family = AF_UNIX;
	strcpy(sun.sun_path, path);
	len = strlen(path);
	*(sun.sun_path + len) = 0;
	slen = sizeof(sun);

	create_socket(&iter_sfd);
	bind_socket(iter_sfd, (const struct sockaddr*)&sun, slen);
	sleep(sleep_t << 2);

	for (;;)
	{
		if (client_num == num_of_clients_to_handle - 1)
			break;
		alarm(alarm_t);
		recieve_datagram(iter_sfd, datagram, datagram_cap, NULL, NULL);
		len = strlen(datagram);
		if (len && !flag)
		{
			*(datagram + len) = 0;
			printf("server recieved datagram - %s\n", datagram);
		}
		counter++;
		if (counter == 1)
		{
			search(datagram, ppath, &s);
			printf("PPATH - %s\n", ppath);
			*datagram = 0;
			continue;
		}
		len = strlen(ppath);
		if (len)
		{
			strcat(ppath, back_slash);
			strcat(ppath, datagram);
			printf("ITERATIVE_SERVER_%s\n", ppath);
			errno = 0;
			fd = open(ppath, O_CREAT | O_TRUNC | O_WRONLY, 0666);
			if (fd == -1)
			{
				perror("iterative::fcntl()\n");
				exit(1);
			}
			write(fd, ppath, len);
			close(fd);
		}
#if 0		
		*ppath = 0;
		*datagram = 0;
#else
		clean_buf(ppath);
		clean_buf(datagram);
#endif		
		flag = 0;
		counter = 0;
		client_num++;
		sleep(sleep_t);
	}

	pop(&s);
	close_socket(iter_sfd);
	delete_socket_file(path);
	exit(0);
}
