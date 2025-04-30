% driver_run_all.m  (project root)
root = fileparts(mfilename('fullpath'));
addpath(fullfile(root,'util'), ...
        genpath('../../libflameatlab'), ...
        fullfile(root,'functions'), ...
        fullfile(root,'tests'));

% ------------------------------------------------------------------
% Register every unit-test function you want to run here.
% ------------------------------------------------------------------
tests = { ...
    'run_Trmm_lltn_unb_var3_tests', ...
    'run_Trmm_lltn_blk_var3_tests', ...
    'run_Syrk_ln_unb_var5_tests', ...
    'run_Syrk_ln_blk_var5_tests' %  ← new!
    };


passed = {};
for k = 1:numel(tests)
    fprintf('\nTests for %s\n', tests{k});   % <-- header line
    ok = feval(tests{k});                    % run suite
    if ok
        passed{end+1} = tests{k};
    else
        error('%s FAILED – driver aborted.', tests{k});
    end
end


fprintf('\n---------------------------\n');
fprintf('All %d/%d test functions passed:\n', numel(passed), numel(tests));
fprintf('  • %s\n', passed{:});
fprintf('---------------------------\n');