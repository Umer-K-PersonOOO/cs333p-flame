function [ C_out ] = Syrk_ln_unb_var5( A, C )

  [ AL, AR ] = FLA_Part_1x2( A, 0, 'FLA_LEFT' );

  while size(AL,2) < size(A,2)

      [ A0,  a1,  A2 ] = FLA_Repart_1x2_to_1x3( AL, AR, 1, 'FLA_RIGHT' );

      % C = fla_ger( 1, a1, at1, C );  
      C = fla_syr('Lower triangular', 1, a1, C);
      % C = C + a1 * a1.';
      [ AL, AR ]   = FLA_Cont_with_1x3_to_1x2( A0,  a1,  A2, 'FLA_LEFT' );
  end

  C_out = C;
end
