
/* Copyright 2025 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Umer Khan
                  umerkhan5110@gmail.com
*/

#include "FLAME.h"


int syrk_ln_unb_var5( FLA_Obj A, FLA_Obj C )
{
  FLA_Obj AL, AR, A0, a1, A2;

  FLA_Part_1x2( A, &AL, &AR, 0, FLA_LEFT );

  while ( FLA_Obj_width( AL ) < FLA_Obj_width( A ) ) {

    FLA_Repart_1x2_to_1x3( AL, /**/ AR, &A0, /**/ &a1, &A2,
                           1, FLA_RIGHT );

    /*------------------------------------------------------------*/

    /* C := C + a1 * a1' */
    FLA_Syr( FLA_LOWER_TRIANGULAR, FLA_ONE, a1, C );

    /*------------------------------------------------------------*/

    FLA_Cont_with_1x3_to_1x2( &AL, /**/ &AR, A0, a1, /**/ A2,
                              FLA_LEFT );
  }

  return FLA_SUCCESS;
}

