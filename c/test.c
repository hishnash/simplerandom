
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "simplerandom.h"


int main(void)
{
    SimpleRandomCong_t      cong;
    SimpleRandomSHR3_t      shr3;
    SimpleRandomMWC_t       mwc;
    SimpleRandomKISS_t      kiss;
    SimpleRandomFib_t       fib;
    SimpleRandomLFIB4_t     lfib4;
    SimpleRandomSWB_t       swb;
    SimpleRandomMWC64_t     mwc64;
    SimpleRandomCong2_t     cong2;
    SimpleRandomSHR3_2_t    shr3_2;
    SimpleRandomKISS2_t     kiss2;
    uint32_t                i;
    uint32_t                k;


    /* Cong */
    simplerandom_cong_seed(&cong, UINT32_C(2524969849));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_cong_next(&cong);
    }
    printf("%"PRIu32"\n", k - UINT32_C(1529210297));

    /* SHR3 */
    simplerandom_shr3_seed(&shr3, UINT32_C(4176875757));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_shr3_next(&shr3);
    }
    printf("%"PRIu32"\n", k - UINT32_C(2642725982));

    /* MWC */
    simplerandom_mwc_seed(&mwc, UINT32_C(2374144069), UINT32_C(1046675282));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc_next(&mwc);
    }
    printf("%"PRIu32"\n", k - UINT32_C(904977562));

    /* KISS */
    simplerandom_kiss_seed(&kiss, UINT32_C(2247183469), UINT32_C(99545079), UINT32_C(1017008441), UINT32_C(3259917390));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_kiss_next(&kiss);
    }
    printf("%"PRIu32"\n", k - UINT32_C(1372460312));

    /* Fib */
    simplerandom_fib_seed(&fib, UINT32_C(9983651), UINT32_C(95746118));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_fib_next(&fib);
    }
    printf("%"PRIu32"\n", k - UINT32_C(3519793928));

    /* LFIB4 */
    simplerandom_kiss_seed(&kiss, UINT32_C(12345), UINT32_C(65435), UINT32_C(12345), UINT32_C(34221));
    for (i = 0; i < 256; i++)
    {
        lfib4.t[i] = simplerandom_kiss_next(&kiss);
    }
    simplerandom_lfib4_seed(&lfib4);
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_lfib4_next(&lfib4);
    }
    printf("%"PRIu32"\n", k - UINT32_C(1064612766));

    /* SWB */
    /* The 1999 Marsaglia test code started SWB using
     * LFIB4's state. So we will duplicate that even
     * though it's a bit ugly and not recommended.
     */
    memcpy(swb.t, lfib4.t, sizeof(swb.t));
    simplerandom_swb_seed(&swb);
    swb.c = lfib4.c;
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_swb_next(&swb);
    }
    printf("%"PRIu32"\n", k - UINT32_C(627749721));

    /* Cong2 */
    simplerandom_cong2_seed(&cong2, UINT32_C(123456789));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_cong2_next(&cong2);
    }
    printf("%"PRIu32"\n", k - UINT32_C(410693845));

    /* SHR3_2 */
    simplerandom_shr3_2_seed(&shr3_2, UINT32_C(362436000));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_shr3_2_next(&shr3_2);
    }
    printf("%"PRIu32"\n", k - UINT32_C(1517776246));

#ifdef UINT64_C

    /* MWC64 */
    simplerandom_mwc64_seed(&mwc64, UINT32_C(7654321), UINT32_C(521288629));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc64_next(&mwc64);
    }
    printf("%"PRIu32"\n", k - UINT32_C(3377343606));

    /* KISS2 */
    simplerandom_kiss2_seed(&kiss2, UINT32_C(7654321), UINT32_C(521288629), UINT32_C(123456789), UINT32_C(362436000));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_kiss2_next(&kiss2);
    }
    printf("%"PRIu32"\n", k - UINT32_C(1010846401));

#endif /* defined(UINT64_C) */
}

