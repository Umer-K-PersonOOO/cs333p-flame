% Copyright 2025 The University of Texas at Austin
%
% For licensing information see
%                http://www.cs.utexas.edu/users/flame/license.html
%
% C ← C + A Aᵀ   (lower-stored SYRK, blocked variant)

function [ C_out ] = Syrk_ln_blk_var5( A, AT, C, nb_alg )

  % Partition A by columns, AT by *rows*
  [ AL, AR ]   = FLA_Part_1x2( A,  0, 'FLA_LEFT' );
  [ ATT, ABT ] = FLA_Part_2x1( AT, 0, 'FLA_TOP'  );

  while size(AL,2) < size(A,2)

      b = min( size(AR,2), nb_alg );

      % Pull a b-column panel from A  (m × b)
      [ A0, A1, A2 ] = FLA_Repart_1x2_to_1x3( AL, AR, b, 'FLA_RIGHT' );

      % Pull the corresponding b-row panel from AT  (b × m)
      [ AT0, AT1, AT2 ] = FLA_Repart_2x1_to_3x1( ATT, ABT, b, 'FLA_BOTTOM' );

      % Update C with that panel product
      C = Syrk_ln_unb_var5( A1, AT1, C );

      % Slide partitions
      [ AL, AR ]   = FLA_Cont_with_1x3_to_1x2( A0,  A1,  A2, 'FLA_LEFT'  );
      [ ATT, ABT ] = FLA_Cont_with_3x1_to_2x1( AT0, AT1, AT2, 'FLA_TOP'   );
  end

  C_out = C;
end
