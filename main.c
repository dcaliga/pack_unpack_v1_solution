static char const cvsid[] = "$Id: main.c,v 2.1 2005/06/14 22:16:48 jls Exp $";

/*
 * Copyright 2005 SRC Computers, Inc.  All Rights Reserved.
 *
 *	Manufactured in the United States of America.
 *
 * SRC Computers, Inc.
 * 4240 N Nevada Avenue
 * Colorado Springs, CO 80907
 * (v) (719) 262-0213
 * (f) (719) 262-0223
 *
 * No permission has been granted to distribute this software
 * without the express permission of SRC Computers, Inc.
 *
 * This program is distributed WITHOUT ANY WARRANTY OF ANY KIND.
 */

#include <libmap.h>
#include <stdlib.h>


void subr (int I0[], int sz, int *accum, int64_t *time, int mapnum);


int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, j, sz, ac, accum;
    int *A;
    int64_t tm;
    int mapnum = 0;

    if ((res_map = fopen ("res_map", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_map'\n");
        exit (1);
        }

    if ((res_cpu = fopen ("res_cpu", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_cpu'\n");
        exit (1);
        }

    if (argc < 2) {
	fprintf (stderr, "need even array size (up to 262144) as arg\n");
	exit (1);
	}

    if (sscanf (argv[1], "%d", &sz) < 1) {
	fprintf (stderr, "need even array size (up to 262144) as arg\n");
	exit (1);
	}

    if (sz > 262144) {
	fprintf (stderr, "array size must not be greater than 262144\n");
	exit (1);
	}

    if (sz & 1) {
        fprintf (stderr, "array size must be even\n");
        exit (1);
        }

    A = (int*) Cache_Aligned_Allocate (sz * sizeof (int));

    srandom (99);

    for (i=0, ac=0; i<sz; i++) {
        A[i] = random () & 0xff;
	if (A[i] > 100)
	    ac += A[i];
	}

    fprintf (res_cpu, "%d\n", ac);

    map_allocate (1);

    subr (A, sz, &accum, &tm, mapnum);

    printf ("%lld clocks\n", tm);

    fprintf (res_map, "%d\n", accum);

    map_free (1);

    exit(0);
    }
