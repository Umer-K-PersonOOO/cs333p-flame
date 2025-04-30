/* Copyright 2025 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Ahmad Raeq Ahsen, Saood Usmani, Umer Khan
                  raeqahsen@utexas.edu, usmani.s.0115@utexas.edu, umerkhan5110@gmail.com
*/
#include "FLAME.h"

int trmm_lln_blk_var3( FLA_Obj L, FLA_Obj B, dim_t nb_alg )
{
  FLA_Obj BL, BR, B0, B1, B2;
  dim_t b;

  FLA_Part_1x2( B, &BL, &BR, 0, FLA_LEFT );

  while ( FLA_Obj_width( BL ) < FLA_Obj_width( B ) ) {

    b = min( nb_alg, FLA_Obj_width( BR ) );

    FLA_Repart_1x2_to_1x3( BL, /**/ BR, &B0, /**/ &B1, &B2,
                           b, FLA_RIGHT );

    /*------------------------------------------------------------*/

    /* B1 = L^T * B1; */
    FLA_Trmm( FLA_LEFT,
              FLA_LOWER_TRIANGULAR,
              FLA_TRANSPOSE,
              FLA_NONUNIT_DIAG,
              FLA_ONE, L, B1 );

    /*------------------------------------------------------------*/

    FLA_Cont_with_1x3_to_1x2( &BL, /**/ &BR, B0, B1, /**/ B2,
                              FLA_LEFT );
  }

  return FLA_SUCCESS;
}
