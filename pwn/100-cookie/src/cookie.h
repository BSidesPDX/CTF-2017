/*
 * Copyright (c) 2012-2015 Alexander Taylor <ajtaylor@fuzyll.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#define _GNU_SOURCE

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __SGNET_H__
#define __SGNET_H__

/* Standard Libraries */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <err.h>

#ifdef _DEBUG
#include <assert.h>
#endif

/* Networking Libraries */
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#ifdef _SCTP
#include <netinet/sctp.h>
#endif

/* Service Setup Functions */
	int cookie_listen(const unsigned short, const int, const char *);

	__attribute__ ((noreturn))
	void cookie_server(int, const char *, int (*handler) (int));
	void cookie_privdrop(const char *);
	int cookie_randfd(int);

/* Socket Communication Wrappers */
	int cookie_readn(const int, void *, const unsigned int);
	int cookie_readsn(const int, char *, const unsigned int);
	int cookie_writes(const int, const char *);
	int cookie_writen(const int, const void *, const unsigned int);

	__attribute__ ((format(printf, 2, 3)))
	int cookie_writef(const int, const char *, ...);

#endif

#ifdef __cplusplus
}
#endif
