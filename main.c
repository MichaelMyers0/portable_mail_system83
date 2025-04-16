#include "sock_lib.h"
enum {num_of_clients = 2};
enum {time_to_sleep = 5};
//this file is a composer, that sends message to the iterative server, that resends all messages to the reciever
main(argc, argv)
int argc;
char** argv;
{
	int sfd, i, cnum;
	const char* fpath = "client_socket";
	const char* fpath1 = "iterative_server_socket";
	struct sockaddr_un sun, sun1;
	size_t len;
	socklen_t slen;
	char datagram[datagram_cap];

	if (argc < 3)
	{
		fprintf(stderr, "ERROR: Provide arguments");
		exit(1);
	}

	sun.sun_family = AF_UNIX;
	strcpy(sun.sun_path, fpath);
	len = strlen(fpath);
	*(sun.sun_path + len) = 0;
	slen = sizeof(sun);

	create_socket(&sfd);
	bind_socket(sfd, (const struct sockaddr*)&sun, slen);
	sun1.sun_family = AF_UNIX;
	strcpy(sun1.sun_path, fpath1);
	len = strlen(sun1.sun_path);
	*(sun1.sun_path + len) = 0;
	slen = sizeof(sun1);

	i = 0;
	cnum = 0;
	for (;;)
	{
		i++;
		strcpy(datagram, *(argv + i));
		len = strlen(datagram);
		*(datagram + len) = 0;
		send_datagram(sfd, datagram, len, (const struct sockaddr*)&sun1, slen);
		*datagram = 0;
		//i++;
		sleep(time_to_sleep);
		if (i == 2)
			break;
	}

	close_socket(sfd);
	delete_socket_file(fpath);

	exit(0);
}
