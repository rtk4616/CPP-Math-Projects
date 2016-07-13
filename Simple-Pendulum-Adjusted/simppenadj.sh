#!/bin/sh
gnuplot -p -c simppenadj.gp
pdflatex simppenadj.tex
okular simppenadj.pdf
