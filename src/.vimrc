syntax on

filetype on
filetype indent on
filetype plugin on
filetype plugin indent on

set ruler
set number "show the line number
set laststatus=2 "always displays statusline
set autoindent "inherit the way of indent in the previous line
"provides indent for c
set smartindent
set cindent
set softtabstop=4
set shiftwidth=4

set foldmethod=syntax

" Make netrw change dir while exploring
let g:netrw_keepdir = 0

" Put these lines at the very end of your vimrc file.
"
" Load all plugins now.
" Plugins need to be added to runtimepath before helptags can be generated.
packloadall
" Load all of the helptags now, after plugins have been loaded.
" All messages and errors will be ignored.
silent! helptags ALL

" Use F8 to open/close tagbar
nmap <F8> :TagbarToggle<CR>
