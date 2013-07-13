#include "ping.h"

int 	datalen = 56;

int 	sockfd;
struct addrinfo* ai;
pid_t	pid;
int 	nsent;
char host[INET_ADDRSTRLEN];

void pinit(char* node)
{
	struct addrinfo hints;
	int ret;
	struct sockaddr_in* sin;
	struct protoent* prent;
	int proto;
	int size;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_flags = AI_CANONNAME;

	if ( (ret = getaddrinfo(node, NULL, &hints, &ai)) != 0) {
		fprintf(stderr, "gettaddrinfo failed: %s\n", gai_strerror(ret));
		exit(EXIT_FAILURE);
	}

	sin = (struct sockaddr_in*) ai->ai_addr;
	inet_ntop(AF_INET, &(sin->sin_addr), host, INET_ADDRSTRLEN);

	printf("PING %s (%s) %d data bytes of data.\n", ai->ai_canonname,
			host, datalen);

	prent = getprotobyname("icmp");
	proto = prent->p_proto;
	sockfd = socket(AF_INET, SOCK_RAW, proto);
	if (-1 == sockfd) {
		if (errno == EPERM) {
			fprintf(stderr, "socket(): Operation not permitted, are you root?\n");
		} else {
			perror("socket()");
		}
		exit(EXIT_FAILURE);
	}

	setuid(getuid());

	size = 60 * 1024;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
}

unsigned short in_cksum(unsigned short* addr, int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	unsigned short answer = 0;

	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	if (nleft == 1) {
		*(unsigned char *) (&answer) = *(unsigned char*) w;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return (answer);
}

void psend()
{
	int len;
	struct icmp* icmp;
	char sendbuf[BUFSIZE];

	icmp = (struct icmp *) sendbuf;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = pid;
	icmp->icmp_seq = nsent++;
	gettimeofday((struct timeval *) icmp->icmp_data, NULL);

	len = 8 + datalen;
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = in_cksum((u_short *) icmp, len);

	sendto(sockfd, sendbuf, len, 0, ai->ai_addr, ai->ai_addrlen);
}

double tv_sub(struct timeval* tve, struct timeval* tvs) {
	// e (end), s (start)

	double mse, mss;  // milli seconds

	mse = tve->tv_sec * 1000.0 + tve->tv_usec / 1000.0;
	mss = tvs->tv_sec * 1000.0 + tvs->tv_usec / 1000.0;

	return (mse - mss);
}

void pproc(char* buf, ssize_t len, struct timeval* tvrecv)
{
	int hlen1;
	int icmplen;
	double rtt;
	struct ip* ip;
	struct icmp* icmp;
	struct timeval* tvsend;

	ip = (struct ip *) buf;
	hlen1 = ip->ip_hl << 2;

	icmp = (struct icmp *) (buf + hlen1);
	if ( (icmplen = len - hlen1) < 8) {
		fprintf(stderr, "icmplen (%d) < 8\n", icmplen);
		exit(EXIT_FAILURE);
	}

	if (ICMP_ECHOREPLY == icmp->icmp_type) {
		if (icmp->icmp_id != pid)
			return;

		if (icmplen < 16) {
			fprintf(stderr, "icmplen (%d) < 16\n", icmplen);
			exit(EXIT_FAILURE);
		}

		tvsend = (struct timeval *) icmp->icmp_data;
		rtt = tv_sub(tvrecv, tvsend);

		printf("%d bytes from %s (%s): icmp_seq=%u, ttl=%d, rtt=%.3f ms\n",
				icmplen, ai->ai_canonname, host,
				icmp->icmp_seq, ip->ip_ttl, rtt);
	}
}

void recvloop()
{
	socklen_t len;
	ssize_t n;
	struct sockaddr sarecv;
	struct timeval tval;
	char recvbuf[BUFSIZE];

	while (1) {
		len = ai->ai_addrlen;
		n = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, &sarecv, &len);
		if (n < 0) {
			if (errno == EINTR) {
				continue;
			} else {
				perror("recvfrom");
				exit(EXIT_FAILURE);
			}
		}
		gettimeofday(&tval, NULL);

		pproc(recvbuf, n, &tval);
	}
}
