set key off
set xlabel 't'
set ylabel "theta"
set terminal svg
set out 'simppenadj.svg'
set title "d2y/dx2 = -9.8 cos(x + dy/dx)" font 'Liberation Sans Bold,16';
set style line 1 lc rgb '#0060ad' lt 2 lw 2 pt 0 ps 1.0
plot 'simppenadj.txt' with linespoints ls 1
set out
