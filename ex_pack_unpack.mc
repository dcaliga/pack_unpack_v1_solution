/* $Id: ex05.mc,v 2.1 2005/06/14 22:16:47 jls Exp $ */

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


void subr (int64_t I0[], int sz, int *accum, int64_t *time, int mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, int64_t, MAX_OBM_SIZE)
    int64_t t0, t1;
    
    Stream_64 SA;

    read_timer (&t0);

#pragma src parallel sections
{
#pragma src section
{
    streamed_dma_cpu_64 (&SA, PORT_TO_STREAM, I0, sz*sizeof(int32_t));
}
#pragma src section
{
    int i,v0,v1,ac0,ac1;
    int64_t i64;

    for (i=0;i<sz/2;i++)  {
       get_stream_64 (&SA, &i64);

       split_64to32 (i64, &v0, &v1);
       cg_accum_add_32 (v0, v0>100, 0, i==0, &ac0);
       cg_accum_add_32 (v1, v1>100, 0, i==0, &ac1);
    }

    *accum = ac0 + ac1;
}
}
    read_timer (&t1);
    *time = t1 - t0;

    }
