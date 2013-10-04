/*
 * Test program for SocketCAN CAN_ISOBUS protocol.
 *
 * Attempts to send a message, then read messages using the a CAN_ISOBUS socket.
 *
 *
 * Author: Alex Layton <awlayton@purdue.edu>
 *	   Pat Sabpisal <ssabpisa@purdue.edu>
 *         Yourname <yourname@purdue.edu>
 *
 * Copyright (C) 2013 Purdue University
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 * :::: Pick up data from the ISOBus :::::
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
 
#include "../socketcan-isobus/patched/can.h"
#include "../socketcan-isobus/isobus.h"
//#include "settings_mgr.h

int main(int argc, char *argv[]) {
	

	if(argc < 3){
	  printf("Usage: ./filter vcanN vcanN [-f] [-y] [-k]\n");
	  return EXIT_FAILURE;
	}

	/*WARNING SUPER ULTRA SLOPPY CODE - FOR DEMO PURPOSE ONLY*/
	FILE * fp = fopen(argv[4],"rb");
	int kfp[10] = {0};
	fseek(fp, sizeof(char)*20, SEEK_CUR);
	fread(kfp,sizeof(int),5,fp);	
	//fread(block,sizeof(int),20,fp);
	//printf("%d %d %d %d",kfp[0],kfp[1],kfp[2],kfp[3]);

	int s;
	int nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	int i;
	struct msghdr msg;
	struct iovec iov;
	unsigned int tmp;

	char ctrlmsg[CMSG_SPACE(sizeof(struct timeval))+CMSG_SPACE(sizeof(__u32))];
	struct isobus_mesg mesg;

	if((s = socket(PF_CAN, SOCK_DGRAM, CAN_ISOBUS)) < 0) {
		perror("Error while opening socket");
		return -1;
	}

	/* Set interface name to first argument */
	strcpy(ifr.ifr_name, argv[1]);
	ioctl(s, SIOCGIFINDEX, &ifr);

	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex; 
	//sscanf(argv[2], "%2x", &tmp);
	//addr.can_addr.isobus.addr = tmp;

	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}

	/* Set up filter(s) */
	struct isobus_filter *filts;
	pgn_t pgns[] = {0, 1, 2,3,5};
	int nfilts = sizeof(pgns) / sizeof(pgn_t);
	filts = calloc(nfilts, sizeof(*filts));

	for(i = 0; i < nfilts; i++) {
		/* Filter based on PGN */
		filts[i].pgn = 0; //the list of blocking PGNs from setting file
		filts[i].pgn_mask = CAN_ISOBUS_PGN_MASK;
		/* Don't filter based on DA */
		filts[i].daddr = 0;
		filts[i].daddr_mask = 0;
		/* Don't filter based on SA */
		filts[i].saddr = 0;
		filts[i].saddr_mask = 0;
		/* Receive message that match (1 to reject matches) */
		filts[i].inverted = 0;
	}
	/*DISCLAIMER: due to time constraint, sloppy code is inevitable*/
	filts[0].pgn = kfp[0];
	filts[1].pgn = kfp[1]; 	
	filts[2].pgn = kfp[2];
	filts[3].pgn = kfp[3];
	filts[4].pgn = kfp[4];

	/* Apply filter(s) to socket */
	
	//parsing argument with loop
	if(argc >= 4 && !strcmp(argv[3],"-f")){
		if(setsockopt(s, SOL_CAN_ISOBUS, CAN_ISOBUS_FILTER, filts,
				nfilts * sizeof(*filts)) < 0) {
			perror("setsockopt");
			return -4;
		}
	}

	/* Construct msghdr to use to recevie messages from socket */
	msg.msg_iov = &iov;
	msg.msg_control = &ctrlmsg;
	msg.msg_controllen = sizeof(ctrlmsg);
	msg.msg_iovlen = 1;
	iov.iov_base = &mesg;
	iov.iov_len = sizeof(mesg);

	mesg.pgn = ISOBUS_PGN_REQUEST;
	mesg.dlen = 1;
	mesg.data[0] = 0xAA;

	/* Send an ISOBUS message */
	if(sendto(s, &mesg, sizeof(mesg), 0, (struct sockaddr *)&addr,
				sizeof(addr)) < 0) {
		perror("Error sending");
		return -3;
	}

	/* Listen for ISOBUS messages */
	while(1)
	{
		nbytes = recvmsg(s, &msg, 0);
		if(nbytes == -1)
		{
		   perror("recvmesg");
		   return -1;
		}
                
	 	printf("PGN:%6d data:", mesg.pgn);
		for(i = 0; i < mesg.dlen; i++)
			printf("%02x", mesg.data[i]);
		printf("\n");
		fflush(0);
	}

	return 0;
}

