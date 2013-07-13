/*
 * A ping program for ipv4 connections.
 *
 * This code was derived from the example on page 661
 * of Richard Stevens book UNIX Network Programming (1998).
 */

#ifndef PING_H
#define PING_H

#include <arpa/inet.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1500

void pinit(char* node);

unsigned short in_cksum(unsigned short* addr, int len);

void psend();

void pproc(char* buf, ssize_t n, struct timeval* tval);

void precv();

#endif  /* PING_H */
