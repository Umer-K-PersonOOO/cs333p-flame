% Unit-tests for Syrk_ln_unb_var5( A , C )
% The kernel should return  C + A*A'  (lower-storage SYRK).
% Returns true when every case passes.

function ok = run_Syrk_ln_unb_var5_tests
rng(0);                 % reproducibility
tol = 1e-12;            % numeric tolerance
ok  = true;

% ---------- test matrices ------------------------------------------------
cases = { ...
    struct('name','1×1 edge',    'A',2,                'C',3), ...
    struct('name','3×2 tall',    'A',randn(3,2),       'C',symm(randn(3))), ...
    struct('name','5×5 square',  'A',randn(5,5),       'C',symm(randn(5))), ...
    struct('name','8×3 tall',    'A',randn(8,3),       'C',symm(randn(8))), ...
    struct('name','large 40×10', 'A',randn(40,10),     'C',symm(randn(40))) ...
    };

for c = 1:numel(cases)
    A   = cases{c}.A;      C0 = cases{c}.C;
    C_lower = tril(C0);   % lower-triangular part
    ref = tril(C0 + A*A.');                       % ground truth
    res = Syrk_ln_unb_var5(A,C_lower);        % routine under test
    err = max(abs(res(:)-ref(:)));
    pass= err < tol*(1+max(abs(ref(:))));
    ok  = ok && pass;
    fprintf('Case %-13s : %s (err = %.2e)\n', ...
            cases{c}.name, tern(pass,'PASS','FAIL'), err);
end
end

% ---------- helpers ------------------------------------------------------
function t = tern(c,a,b), if c, t = a; else, t = b; end, end
function S = symm(M),      S = 0.5*(M+M.');                     end
