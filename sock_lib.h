#ifndef SOCK_LIB_H
#define SOCK_LIB_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
extern volatile sig_atomic_t flag;
enum {datagram_cap = 512};
typedef void (*handler_t)(int);
create_socket(sfd);
bind_socket(sfd, addr, slen);
send_datagram(sfd, buf, size, dst_addr, dst_size);
recieve_datagram(sfd, buf, size, dst_addr, dst_size);
close_socket(sfd);
delete_socket_file(name);
change_signal_disposition();
#endif
