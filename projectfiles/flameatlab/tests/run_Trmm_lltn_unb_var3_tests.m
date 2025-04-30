% test/run_Trmm_lltn_unb_var3_tests.m
function ok = run_Trmm_lltn_unb_var3_tests
rng(0);  tol = 1e-12;  ok = true;
cases = { ...
    struct('name','1×1 edge',         'L',3,                      'B',7), ...
    struct('name','4×4 square',       'L',tril(randn(4)),         'B',randn(4,4)), ...
    struct('name','8×5 rectangular',  'L',tril(randn(8)),         'B',randn(8,5)), ...
    struct('name','unit diag',        'L',unitdiag(tril(randn(6))),'B',randn(6,3)), ...
    struct('name','singular (0 diag)','L',singularL(tril(randn(5))),'B',randn(5,4)), ...
    struct('name','large random',     'L',tril(randn(50)),        'B',randn(50,20)) };
for k = 1:numel(cases)
    L = cases{k}.L;  B = cases{k}.B;
    ref = L' * B;                           % ground truth
    res = Trmm_lltn_unb_var3(L,B);          % routine under test
    err = max(abs(res(:)-ref(:)));
    pass = err < tol*(1+max(abs(ref(:))));
    ok   = ok && pass;
    fprintf('Case %-13s : %s (err = %.2e)\n', ...
            cases{k}.name, tern(pass,'PASS','FAIL'), err);
end
end
function t = tern(c,a,b),  t = a;  if ~c, t = b; end, end
function L = unitdiag(L),  L = L - diag(diag(L)) + eye(size(L)); end
function L = singularL(L), L(1,1) = 0;                             end
