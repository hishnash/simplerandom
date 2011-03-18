
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "simplerandom.h"


int main(void)
{
    SimpleRandomCong_t      cong;
    SimpleRandomSHR3_t      shr3;
    SimpleRandomMWC1_t      mwc1;
    SimpleRandomMWC2_t      mwc2;
    SimpleRandomKISS_t      kiss;
    SimpleRandomLFIB4_t     lfib4;
    SimpleRandomSWB_t       swb;
    SimpleRandomMWC64_t     mwc64;
    SimpleRandomKISS2_t     kiss2;
    SimpleRandomLFSR113_t   lfsr113;
    SimpleRandomLFSR88_t    lfsr88;
    uint32_t                i;
    uint32_t                k;


    /* Cong */
    simplerandom_cong_seed(&cong, UINT32_C(2051391225));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_cong_next(&cong);
    }
    printf("Cong        %"PRIu32"\n", k - UINT32_C(2416584377));

    /* SHR3 */
    simplerandom_shr3_seed(&shr3, UINT32_C(3360276411));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_shr3_next(&shr3);
    }
    printf("SHR3        %"PRIu32"\n", k - UINT32_C(1153302609));

    /* MWC1 */
    simplerandom_mwc1_seed(&mwc1, UINT32_C(2374144069), UINT32_C(1046675282));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc1_next(&mwc1);
    }
    printf("MWC1        %"PRIu32"\n", k - UINT32_C(904977562));

    /* MWC2 */
    simplerandom_mwc2_seed(&mwc2, UINT32_C(12345), UINT32_C(65437));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc2_next(&mwc2);
    }
    printf("MWC2        %"PRIu32"\n", k - UINT32_C(55050263));

    /* KISS */
    simplerandom_kiss_seed(&kiss, UINT32_C(2247183469), UINT32_C(99545079), UINT32_C(3269400377), UINT32_C(3950144837));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_kiss_next(&kiss);
    }
    printf("KISS        %"PRIu32"\n", k - UINT32_C(2100752872));

    /* LFIB4 */
    /* Below are 2 different seed methods, which should be equivalent */
#if 0
    simplerandom_kiss_seed(&kiss, UINT32_C(12345), UINT32_C(65435), UINT32_C(12345), UINT32_C(34221));
    for (i = 0; i < 256; i++)
    {
        lfib4.t[i] = simplerandom_kiss_next(&kiss);
    }
    simplerandom_lfib4_seed(&lfib4);
#else
    simplerandom_lfib4_seed_from_kiss(&lfib4, UINT32_C(12345), UINT32_C(65435), UINT32_C(12345), UINT32_C(34221));
#endif
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_lfib4_next(&lfib4);
    }
    printf("LFIB4       %"PRIu32"\n", k - UINT32_C(3874012728));

    /* SWB */
    /* The 1999 Marsaglia test code ran SWB using LFIB4's
     * state after the LFIB4 test. So we will duplicate
     * that even though it's a bit ugly and not
     * recommended.
     */
    memcpy(swb.t, lfib4.t, sizeof(swb.t));
    simplerandom_swb_seed(&swb);
    swb.c = lfib4.c;
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_swb_next(&swb);
    }
    printf("SWB         %"PRIu32"\n", k - UINT32_C(1831941512));

#ifdef UINT64_C

    /* MWC64 */
    simplerandom_mwc64_seed(&mwc64, UINT32_C(7654321), UINT32_C(521288629));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc64_next(&mwc64);
    }
    printf("MWC64       %"PRIu32"\n", k - UINT32_C(3377343606));

    /* KISS2 */
    simplerandom_kiss2_seed(&kiss2, UINT32_C(7654321), UINT32_C(521288629), UINT32_C(123456789), UINT32_C(362436000));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_kiss2_next(&kiss2);
    }
    printf("KISS2       %"PRIu32"\n", k - UINT32_C(1010846401));

#endif /* defined(UINT64_C) */

    /* LFSR113 */
    simplerandom_lfsr113_seed(&lfsr113, UINT32_C(12345), UINT32_C(12345), UINT32_C(12345), UINT32_C(12345));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_lfsr113_next(&lfsr113);
    }
    printf("LFSR113     %"PRIu32"\n", k - UINT32_C(1205173390));

    /* LFSR88 */
    simplerandom_lfsr88_seed(&lfsr88, UINT32_C(12345), UINT32_C(12345), UINT32_C(12345));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_lfsr88_next(&lfsr88);
    }
    printf("LFSR88      %"PRIu32"\n", k - UINT32_C(3639585634));

}

