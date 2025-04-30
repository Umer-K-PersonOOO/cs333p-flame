#include <stdio.h>
#include <math.h>
#include <time.h>

#include "FLAME.h"

/* Various constants that control what gets timed */

#define TRUE 1
#define FALSE 0

int syrk_ln_unb_var5( FLA_Obj, FLA_Obj );
int syrk_ln_blk_var5( FLA_Obj, FLA_Obj, dim_t );
int trmm_lln_unb_var3( FLA_Obj, FLA_Obj );
int trmm_lln_blk_var3( FLA_Obj, FLA_Obj, dim_t );

int main(int argc, char *argv[])
{
    int n, nfirst, nlast, ninc, i, irep, nrepeats, nb_alg;

    double
        dtime, dtime_best, 
        diff;

    FLA_Obj
        Aobj, Cobj, Cold, Cref,
        Lobj, Bobj, Bold, Bref;

    /* Initialize FLAME */
    FLA_Init( );

    /* Every time trial is repeated "repeat" times and the fastest run in recorded */
    printf( "%% number of repeats:" );
    scanf( "%d", &nrepeats );
    printf( "%% %d\n", nrepeats );

    /* Timing trials for matrix sizes n=nfirst to nlast in increments 
       of ninc will be performed. */
    printf( "%% enter nfirst, nlast, ninc:" );
    scanf( "%d%d%d", &nfirst, &nlast, &ninc );
    printf( "%% %d %d %d \n", nfirst, nlast, ninc );
    fflush( stdout );

    /* Read block size for blocked variant */
    printf("%% enter block size nb_alg:");
    scanf("%d", &nb_alg);
    printf("%% %d\n", nb_alg);
    fflush(stdout);

    i = 1;
    for (n = nfirst; n <= nlast; n += ninc) {
        printf("(%d, 1:0) = [size, speed, error ];\n", i);
        fflush(stdout);
        // SYRK TESTS 

        /* Create matrices for SYRK */
        FLA_Obj_create(FLA_DOUBLE, n, n, 0, 0, &Aobj);
        FLA_Obj_create(FLA_DOUBLE, n, n, 0, 0, &Cobj);
        FLA_Obj_create(FLA_DOUBLE, n, n, 0, 0, &Cold);
        FLA_Obj_create(FLA_DOUBLE, n, n, 0, 0, &Cref);

        FLA_Random_matrix(Aobj);
        FLA_Random_symm_matrix(FLA_LOWER_TRIANGULAR, Cold);

        /* Reference SYRK: Cref := AA^T + Cref  */
        dtime_best = 1.0e9;
        for (irep = 0; irep < nrepeats; irep++) {
            FLA_Copy(Cold, Cref);
            dtime = FLA_Clock();

            FLA_Syrk(FLA_LOWER_TRIANGULAR, FLA_NO_TRANSPOSE,
                     FLA_ONE, Aobj, FLA_ONE, Cref);

            dtime = FLA_Clock() - dtime;
            dtime_best = (dtime < dtime_best ? dtime : dtime_best);
        }
        printf("data_ref_syrk(%d, 1:2) = [ %d %le ];\n", i, n, dtime_best);
        fflush(stdout);

        /* SYRK unblocked */
        dtime_best = 1.0e9;
        for (irep = 0; irep < nrepeats; irep++) {
            FLA_Copy(Cold, Cobj);
            dtime = FLA_Clock();

            syrk_ln_unb_var5(Aobj, Cobj);

            dtime = FLA_Clock() - dtime;
            dtime_best = (dtime < dtime_best ? dtime : dtime_best);
        }
        diff = FLA_Max_elemwise_diff(Cobj, Cref);
        printf("data_unb_var5_syrk(%d, 1:3) = [ %d %le %le ];\n", i, n, dtime_best, diff);
        fflush(stdout);

        /* SYRK blocked */
        dtime_best = 1.0e9;
        for (irep = 0; irep < nrepeats; irep++) {
            FLA_Copy(Cold, Cobj);
            dtime = FLA_Clock();

            syrk_ln_blk_var5(Aobj, Cobj, nb_alg);

            dtime = FLA_Clock() - dtime;
            dtime_best = (dtime < dtime_best ? dtime : dtime_best);
        }
        diff = FLA_Max_elemwise_diff(Cobj, Cref);
        printf("data_blk_var5_syrk(%d, 1:3) = [ %d %le %le ];\n", i, n, dtime_best, diff);
        fflush(stdout);

        FLA_Obj_free(&Aobj);
        FLA_Obj_free(&Cobj);
        FLA_Obj_free(&Cold);
        FLA_Obj_free(&Cref);

        // --- TRMM TESTS -------------------------------------------------------

        /* Create matrices for TRMM */
        FLA_Obj_create(FLA_DOUBLE, n, n, 0, 0, &Lobj);
        FLA_Obj_create(FLA_DOUBLE, n, n, 0, 0, &Bobj);
        FLA_Obj_create(FLA_DOUBLE, n, n, 0, 0, &Bold);
        FLA_Obj_create(FLA_DOUBLE, n, n, 0, 0, &Bref);

        FLA_Random_matrix(Lobj);
        FLA_Triangularize(FLA_LOWER_TRIANGULAR, FLA_NONUNIT_DIAG, Lobj);

        FLA_Random_matrix(Bold);

        /* Reference TRMM: Bref := tril(L) * Bref */
        dtime_best = 1.0e9;
        for (irep = 0; irep < nrepeats; irep++) {
            FLA_Copy(Bold, Bref);
            dtime = FLA_Clock();

            FLA_Trmm(FLA_LEFT, FLA_LOWER_TRIANGULAR,
                     FLA_TRANSPOSE, FLA_NONUNIT_DIAG,
                     FLA_ONE, Lobj, Bref);

            dtime = FLA_Clock() - dtime;
            dtime_best = (dtime < dtime_best ? dtime : dtime_best);
        }
        printf("data_ref_trmm(%d, 1:2) = [ %d %le ];\n", i, n, dtime_best);
        fflush(stdout);

        /* TRMM unblocked */
        dtime_best = 1.0e9;
        for (irep = 0; irep < nrepeats; irep++) {
            FLA_Copy(Bold, Bobj);
            dtime = FLA_Clock();

            trmm_lln_unb_var3(Lobj, Bobj);

            dtime = FLA_Clock() - dtime;
            dtime_best = (dtime < dtime_best ? dtime : dtime_best);
        }
        diff = FLA_Max_elemwise_diff(Bobj, Bref);
        printf("data_unb_var3_trmm(%d, 1:3) = [ %d %le %le ];\n", i, n, dtime_best, diff);
        fflush(stdout);

        /* TRMM blocked */
        dtime_best = 1.0e9;
        for (irep = 0; irep < nrepeats; irep++) {
            FLA_Copy(Bold, Bobj);
            dtime = FLA_Clock();

            trmm_lln_blk_var3(Lobj, Bobj, nb_alg);

            dtime = FLA_Clock() - dtime;
            dtime_best = (dtime < dtime_best ? dtime : dtime_best);
        }
        diff = FLA_Max_elemwise_diff(Bobj, Bref);
        printf("data_blk_var3_trmm(%d, 1:3) = [ %d %le %le ];\n", i, n, dtime_best, diff);
        fflush(stdout);

        FLA_Obj_free(&Lobj);
        FLA_Obj_free(&Bobj);
        FLA_Obj_free(&Bold);
        FLA_Obj_free(&Bref);

        i++;
    }
    printf("We found 10 to be the optimal blocksize that improves performance, with larger numbers decreasing performance.\n");
    FLA_Finalize();
    return 0;
}