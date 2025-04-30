/* Copyright 2025 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Ahmad Raeq Ahsen, Saood Usmani, Umer Khan
                  raeqahsen@utexas.edu, usmani.s.0115@utexas.edu, umerkhan5110@gmail.com
*/
#include "FLAME.h"

int trmm_lln_unb_var3( FLA_Obj L, FLA_Obj B )
{
  FLA_Obj BL, BR, B0, b1, B2;

  FLA_Part_1x2( B, &BL, &BR, 0, FLA_LEFT );

  while ( FLA_Obj_width( BL ) < FLA_Obj_width( B ) ) {

    FLA_Repart_1x2_to_1x3( BL, /**/ BR, &B0, /**/ &b1, &B2,
                           1, FLA_RIGHT );

    /*------------------------------------------------------------*/

    /* b1 = L^T * b1; */
    FLA_Trmv( FLA_LOWER_TRIANGULAR,
                       FLA_TRANSPOSE,
                       FLA_NONUNIT_DIAG, L, b1 );

    /*------------------------------------------------------------*/

    FLA_Cont_with_1x3_to_1x2( &BL, /**/ &BR, B0, b1, /**/ B2,
                              FLA_LEFT );
  }

  return FLA_SUCCESS;
}
