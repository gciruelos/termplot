# termplot
[![Build Status](https://travis-ci.org/gciruelos/termplot.svg?branch=master)](https://travis-ci.org/gciruelos/termplot)

Lightweight terminal-based mathematical function plotter.

# Try it out

First you have to clone the repository

    git clone https://github.com/gciruelos/termplot.git
    cd termplot

If you have termbox, you can compile `termplot` by running

    make termbox

Otherwise, you can use the old-fashioned ncurses

    make ncurses

Then run it

    ./termplot
    ./termplot --help

# Official packages

* Archlinux (AUR): [termplot](https://aur.archlinux.org/packages/termplot/).

# How to use

Termplot supports vim-like commands, so you can type

    :plot sin(x^2)

And it will work. Termplot can also plot implicit functions, like

    :plot x^2+y^2 = 1

# Screenshots
![![Screen](https://raw.githubusercontent.com/gciruelos/termplot/master/img/screen1.png)](img/screen1.png "Screenshot")

# TODO

* Zooming just in one axis.
* Replacing plots.
* Read from commandline/stdin.
* Better documentation.

# Contributors

* [Yu-Jie Lin](https://github.com/livibetter)


