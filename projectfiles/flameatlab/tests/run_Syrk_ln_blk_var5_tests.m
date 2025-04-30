function ok = run_Syrk_ln_blk_var5_tests
rng(0);  tol = 1e-12;  ok = true;

cases = { ...
    struct('name','1×1 edge',    'A',2,                'C',symm(randn(1))), ...
    struct('name','3×2 tall',    'A',randn(3,2),       'C',symm(randn(3))), ...
    struct('name','5×5 square',  'A',randn(5,5),       'C',symm(randn(5))), ...
    struct('name','8×3 tall',    'A',randn(8,3),       'C',symm(randn(8))), ...
    struct('name','40×10 large', 'A',randn(40,10),     'C',symm(randn(40))) ...
    };

nb_list = [1 2 3 4 8 16 64];     % block sizes to sweep

for c = 1:numel(cases)
    A = cases{c}.A;  AT = A.';  C0 = cases{c}.C;
    ref = C0 + A*A.';
    for nb = nb_list
        res = Syrk_ln_blk_var5(A,AT,C0,nb);
        err = max(abs(res(:)-ref(:)));
        pass = err < tol*(1+max(abs(ref(:))));
        ok   = ok && pass;
        fprintf('Case %-14s nb=%-3d : %s (err = %.2e)\n', ...
                 cases{c}.name, nb, tern(pass,'PASS','FAIL'), err);
    end
end
end

% ---------- helpers ----------
function t = tern(c,a,b), if c, t = a; else, t = b; end, end
function S = symm(M),      S = 0.5*(M+M.');               end
