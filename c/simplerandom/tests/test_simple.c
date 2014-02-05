
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "simplerandom.h"
#include "bitcolumnmatrix.h"

static int test_multi(void)
{
    SimpleRandomCong_t      cong;
    SimpleRandomSHR3_t      shr3;
    SimpleRandomMWC1_t      mwc1;
    SimpleRandomMWC2_t      mwc2;
    SimpleRandomKISS_t      kiss;
    SimpleRandomMWC64_t     mwc64;
    SimpleRandomKISS2_t     kiss2;
    SimpleRandomLFSR113_t   lfsr113;
    SimpleRandomLFSR88_t    lfsr88;
    uint32_t                i;
    uint32_t                k;


    printf("1,000,000 sample tests\n");
    /* Cong */
    simplerandom_cong_seed(&cong, UINT32_C(2051391225));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_cong_next(&cong);
    }
    printf("    Cong        %"PRIu32"\n", k - UINT32_C(2416584377));

    /* SHR3 */
    simplerandom_shr3_seed(&shr3, UINT32_C(3360276411));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_shr3_next(&shr3);
    }
    printf("    SHR3        %"PRIu32"\n", k - UINT32_C(1153302609));

    /* MWC1 */
    simplerandom_mwc1_seed(&mwc1, UINT32_C(2374144069), UINT32_C(1046675282));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc1_next(&mwc1);
    }
    printf("    MWC1        %"PRIu32"\n", k - UINT32_C(904977562));

    /* MWC2 */
    simplerandom_mwc2_seed(&mwc2, UINT32_C(12345), UINT32_C(65437));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc2_next(&mwc2);
    }
    printf("    MWC2        %"PRIu32"\n", k - UINT32_C(55050263));

    /* KISS */
    simplerandom_kiss_seed(&kiss, UINT32_C(2247183469), UINT32_C(99545079), UINT32_C(3269400377), UINT32_C(3950144837));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_kiss_next(&kiss);
    }
    printf("    KISS        %"PRIu32"\n", k - UINT32_C(2100752872));

#ifdef UINT64_C

    /* MWC64 */
    simplerandom_mwc64_seed(&mwc64, UINT32_C(7654321), UINT32_C(521288629));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc64_next(&mwc64);
    }
    printf("    MWC64       %"PRIu32"\n", k - UINT32_C(3377343606));

    /* KISS2 */
    simplerandom_kiss2_seed(&kiss2, UINT32_C(7654321), UINT32_C(521288629), UINT32_C(123456789), UINT32_C(362436000));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_kiss2_next(&kiss2);
    }
    printf("    KISS2       %"PRIu32"\n", k - UINT32_C(1010846401));

#endif /* defined(UINT64_C) */

    /* LFSR113 */
    simplerandom_lfsr113_seed(&lfsr113, 0, 0, 0, 0);
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_lfsr113_next(&lfsr113);
    }
    printf("    LFSR113     %"PRIu32"\n", k - UINT32_C(300959510));

    /* LFSR88 */
    simplerandom_lfsr88_seed(&lfsr88, 0, 0, 0);
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_lfsr88_next(&lfsr88);
    }
    printf("    LFSR88      %"PRIu32"\n", k - UINT32_C(3774296834));

    printf("\n");
    return 0;
}

static void print_matrix(const char * p_title, const BitColumnMatrix32_t * p_matrix)
{
    size_t      i;

    printf("%s\n", p_title);
    for (i = 0; i < 32u; ++i)
    {
        if (i && !(i % 8))
            printf("\n");
        if (!(i % 8))
            printf("    ");
        printf("%08"PRIX32" ", p_matrix->matrix[i]);
    }
    printf("\n");
}

static void calc_shr3_matrix(void)
{
    BitColumnMatrix32_t     unity, shr3_temp, shr3_a, shr3_b, shr3_c, shr3_matrix;

    bitcolumnmatrix32_unity(&shr3_a);
    bitcolumnmatrix32_shift(&shr3_temp, 13);
    bitcolumnmatrix32_iadd(&shr3_a, &shr3_temp);

    bitcolumnmatrix32_unity(&shr3_b);
    bitcolumnmatrix32_shift(&shr3_temp, -17);
    bitcolumnmatrix32_iadd(&shr3_b, &shr3_temp);

    bitcolumnmatrix32_unity(&shr3_c);
    bitcolumnmatrix32_shift(&shr3_temp, 5);
    bitcolumnmatrix32_iadd(&shr3_c, &shr3_temp);

    bitcolumnmatrix32_unity(&shr3_matrix);
    bitcolumnmatrix32_imul(&shr3_matrix, &shr3_c);
    bitcolumnmatrix32_imul(&shr3_matrix, &shr3_b);
    bitcolumnmatrix32_imul(&shr3_matrix, &shr3_a);

    print_matrix("SHR3 BitColumnMatrix32_t matrix", &shr3_matrix);
}

int main(void)
{
    int ret_val;

    calc_shr3_matrix();

    ret_val = test_multi();
    if (ret_val != 0)
        return ret_val;

    return 0;
}

