function [ C_out ] = Syrk_ln_unb_var5( A, AT, C )

  [ AL, AR ] = FLA_Part_1x2( A, 0, 'FLA_LEFT' );

  [ ATT, ABT ] = FLA_Part_2x1( AT, 0, 'FLA_TOP' );

  while size(AL,2) < size(A,2)

      [ A0,  a1,  A2 ] = FLA_Repart_1x2_to_1x3( AL, AR, 1, 'FLA_RIGHT' );
      [ AT0, at1, AT2 ] = FLA_Repart_2x1_to_3x1( ATT, ABT, 1, 'FLA_BOTTOM' );

      C = fla_ger( 1, a1, at1, C );   

      [ AL, AR ]   = FLA_Cont_with_1x3_to_1x2( A0,  a1,  A2, 'FLA_LEFT' );
      [ ATT, ABT ] = FLA_Cont_with_3x1_to_2x1( AT0, at1, AT2, 'FLA_TOP' );
  end

  C_out = C;
end
