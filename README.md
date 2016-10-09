# termplot
[![Build Status](https://travis-ci.org/gciruelos/termplot.svg?branch=master)](https://travis-ci.org/gciruelos/termplot)

Terminal-based mathematical function plotter

# Try it out

First you have to clone the repository

    git clone https://github.com/gciruelos/termplot.git
    cd termplot

Now build and run

    make
    ./termplot

#How to use

Termplot supports vim-like commands, so you can type
    
    :plot sin(x^2)

And it will work. Termplot can also plot implicit functions, like

    :plot x^2+y^2 = 1

#Screenshots
![![Scren](https://raw.githubusercontent.com/gciruelos/termplot/master/info/screen1.png)](info/screen1.png "Screenshot")

#TODO

* Zooming just in one axis
* Deleting plots
* Replacing plots
* Write out to files
* Read from commandline/stdin
* Different plot styles?
* Less flicker

#Contributors

* [Yu-Jie Lin](https://github.com/livibetter)


