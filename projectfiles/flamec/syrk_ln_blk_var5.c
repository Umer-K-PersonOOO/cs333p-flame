/* Copyright 2025 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Umer Khan
                  umerkhan5110@gmail.com
*/


#include "FLAME.h"

FLA_Error syrk_ln_blk_var5( FLA_Obj A, FLA_Obj C, dim_t nb_alg )
{
  FLA_Obj AL, AR, A0, A1, A2;
  dim_t b;

  FLA_Part_1x2( A, &AL, &AR, 0, FLA_LEFT );

  while ( FLA_Obj_width( AL ) < FLA_Obj_width( A ) ) {

    b = min( nb_alg, FLA_Obj_width( AR ) );

    FLA_Repart_1x2_to_1x3( AL, /**/ AR, &A0, /**/ &A1, &A2,
                           b, FLA_RIGHT );

    /*------------------------------------------------------------*/

    /* C := C + A1 * A1ᵀ */
    FLA_Syrk( FLA_LOWER_TRIANGULAR,
              FLA_NO_TRANSPOSE,
              FLA_ONE, A1,
              FLA_ONE, C );

    /*------------------------------------------------------------*/

    FLA_Cont_with_1x3_to_1x2( &AL, /**/ &AR, A0, A1, /**/ A2,
                              FLA_LEFT );
  }

  return FLA_SUCCESS;
}
