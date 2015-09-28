" Load this with command LoadProjectVim
"
" directory
" Folder in which script resides: (not safe for symlinks)
let s:base_path = expand('<sfile>:p:h')
let s:build_dir = s:base_path . "/build"
let s:bin_dir = s:base_path . "/bin"
let s:bin_name = "Bens-Game"

function! s:EditRootCMakeLists()
    let l:CMakePath = s:base_path . "/CMakeLists.txt"
    execute 'vsplit' l:CMakePath
endfunction
command! EditRootCMakeLists call s:EditRootCMakeLists()

function! s:EditCurrentCMakeLists()
    let l:CMakePath = getcwd() . "/CMakeLists.txt"
    execute 'vsplit' l:CMakePath
endfunction
command! EditCurrentCMakeLists call s:EditCurrentCMakeLists()

command! Make execute '!cd '. s:build_dir . " && make"
command! CMake execute '!cd ' . s:build_dir . " && cmake " . s:base_path

function! s:Run()
    write
    Make
    exec '!cd ' . s:bin_dir . ' && ./' . s:bin_name
endfunction
command! Run call s:Run()
map <F5> :Run<CR>

function! s:RedoYcmGenerateConfig()
    execute 'cd ' . s:base_path
    execute '!rm .ycm_extra_conf.py*'
    YcmGenerateConfig
    execute 'cd -'
endfunction
command! RedoYcmGenerateConfig call s:RedoYcmGenerateConfig()

command! VSIndentStyle set tabstop=4 softtabstop=4 shiftwidth=4 noexpandtab
