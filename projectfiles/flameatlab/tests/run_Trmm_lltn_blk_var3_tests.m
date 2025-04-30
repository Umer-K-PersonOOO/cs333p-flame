% test/run_Trmm_lltn_blk_var3_tests.m
% -------------------------------------------------------------------------
% Unit-tests for the blocked variant  Trmm_lltn_blk_var3( L , B , nb_alg )
% The routine should return  L' * B  for a lower-triangular L.
% Returns true when every case / block-size combination passes.
% -------------------------------------------------------------------------
function ok = run_Trmm_lltn_blk_var3_tests
rng(0);                     % reproducibility
tol = 1e-12;                % numeric tolerance
ok  = true;                 % overall pass flag

% ---- test matrices ------------------------------------------------------
cases = { ...
    struct('name','1×1 edge',         'L',3,                      'B',7), ...
    struct('name','4×4 square',       'L',tril(randn(4)),         'B',randn(4,4)), ...
    struct('name','8×5 rectangular',  'L',tril(randn(8)),         'B',randn(8,5)), ...
    struct('name','unit diag',        'L',unitdiag(tril(randn(6))),'B',randn(6,3)), ...
    struct('name','singular (0 diag)','L',singularL(tril(randn(5))),'B',randn(5,4)), ...
    struct('name','large random',     'L',tril(randn(50)),        'B',randn(50,20)) ...
    };

% ---- block sizes to try -------------------------------------------------
nb_list = [1 2 3 4 8 16 64];    % values > width are fine (routine caps them)

for c = 1:numel(cases)
    L   = cases{c}.L;  B = cases{c}.B;
    ref = L' * B;                          % ground truth
    
    for nb = nb_list
        res = Trmm_lltn_blk_var3(L,B,nb);  % routine under test
        err = max(abs(res(:) - ref(:)));
        pass= err < tol*(1+max(abs(ref(:))));
        ok  = ok && pass;
        fprintf('Case %-13s  nb=%-3d : %s (err = %.2e)\n', ...
                cases{c}.name, nb, tern(pass,'PASS','FAIL'), err);
    end
end
end

% ---- small helpers ------------------------------------------------------
function t = tern(c,a,b), if c, t = a; else, t = b; end, end
function L = unitdiag(L), L = L - diag(diag(L)) + eye(size(L)); end
function L = singularL(L), L(1,1) = 0;                             end
