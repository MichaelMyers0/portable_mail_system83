#include "sock_lib.h"

volatile sig_atomic_t flag = 0;

static void handler(int sig)
{
	flag = 1;
}

create_socket(sfd)
int* sfd;
{
	errno = 0;
	*sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (*sfd == -1)
	{
		perror("create_socket()\n");
		exit(1);
	}
}

bind_socket(sfd, addr, slen)
int sfd;
struct sockaddr* addr;
socklen_t slen;
{
	int res;
	errno = 0;
	res = bind(sfd, addr, slen);
	if (res == -1)
	{
		perror("bind_socket()\n");
		exit(2);
	}
}

send_datagram(sfd, buf, size, dst_addr, dst_size)
int sfd;
char* buf;
size_t size;
const struct sockaddr* dst_addr;
socklen_t dst_size;
{
	ssize_t cnt;
	errno = 0;
	cnt = sendto(sfd, buf, size, 0, dst_addr, dst_size);
	if (cnt == -1)
	{
		perror("send_datagram()\n");
		exit(3);
	}
}

recieve_datagram(sfd, buf, size, dst_addr, dst_size)
int sfd;
char* buf;
size_t size;
struct sockaddr* dst_addr;
socklen_t* dst_size;
{
	ssize_t cnt;
	errno = 0;
	cnt = recvfrom(sfd, buf, size, 0, dst_addr, dst_size);
	if (cnt == -1)
	{
		perror("recieve_datagram()\n");
		exit(4);
	}
}

close_socket(sfd)
int sfd;	
{
	int res;
	errno = 0;
	res = close(sfd);
	if (res == -1)
	{
		perror("close_socket()\n");
		exit(5);
	}
}

delete_socket_file(name)
const char* name;
{
	int res;
	errno = 0;
	res = unlink(name);
	if (res == -1)
	{
		perror("delete_socket_file()\n");
		exit(6);
	}
}

change_signal_disposition()
{
	handler_t old_handler, new_handler;
	new_handler = handler;
	errno = 0;
	old_handler = signal(SIGALRM, new_handler);
	if (old_handler == SIG_ERR)
	{
		perror("channge_signal_disposition()\n");
		exit(7);
	}
}
