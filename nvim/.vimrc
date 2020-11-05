set nocompatible
filetype off

set encoding=utf-8

if has('gui_running')
  set guifont=JetBrains_Mono:h12:cANSI:qDRAFT
endif

syntax on
let g:material_theme_style = 'darker'
let g:airline_theme = 'material'
colorscheme material

" Material color scheme commands?
" For Neovim 0.1.3 and 0.1.4 - https://github.com/neovim/neovim/pull/2198
if (has('nvim'))
  let $NVIM_TUI_ENABLE_TRUE_COLOR = 1
endif

" For Neovim > 0.1.5 and Vim > patch 7.4.1799 - https://github.com/vim/vim/commit/61be73bb0f965a895bfb064ea3e55476ac175162
" Based on Vim patch 7.4.1770 (`guicolors` option) - https://github.com/vim/vim/commit/8a633e3427b47286869aa4b96f2bfc1fe65b25cd
" https://github.com/neovim/neovim/wiki/Following-HEAD#20160511
if (has('termguicolors'))
  set termguicolors
endif

set number

filetype plugin on
set autoindent
set tabstop=4
set shiftwidth=4
set expandtab
set softtabstop=4

let mapleader = ","

" Copy entire file into clipboard
" :map <Leader>y :%y+<Enter>
" Windows WSL clipboard...
:map <Leader>y :silent :w !clip.exe<Enter>

set undofile
set undodir=$HOME/.vim/undo

" Open competitive programming stuff
command M :163
command EI :e ~/competitive-programming/input.txt
command RC :T g++ -o prog -std=c++11 '%' && ./prog
command R :T g++ -o prog -std=c++11 '%' && ./prog < ~/competitive-programming/input.txt
let @q = ':r ~/competitive-programming/main.cppkdd:vs€ül:Tnew:sp:EIdG'

set scrolloff=8

" Terminal mode escape
if has('nvim')
  tnoremap <Esc> <C-\><C-n>
  tnoremap <C-V><Esc> <Esc>
endif

" Terminal Cursor
if has('nvim')
  highlight! link TermCursor Cursor
  highlight! TermCursorNC guibg=red guifg=white ctermbg=1 ctermfg=15
endif
