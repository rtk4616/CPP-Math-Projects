# x vs. t
set key off
set xlabel 't'
set ylabel 'x'
set terminal svg
set out "lorenz-x.svg"
set title 'Lorenz' font 'Liberation Sans Bold,16'
set style line 1 lc rgb '#0060ad' lt 2 lw 2 pt 0 ps 1.0
plot 'lorenz-x.txt' with linespoints ls 1
set out

# y vs t
set key off
set xlabel 't'
set ylabel 'y'
set terminal svg
set out "lorenz-y.svg"
set title 'Lorenz' font 'Liberation Sans Bold,16'
set style line 1 lc rgb '#0060ad' lt 2 lw 2 pt 0 ps 1.0
plot 'lorenz-y.txt' with linespoints ls 1
set out

# z vs t
set key off
set xlabel 't'
set ylabel 'z'
set terminal svg
set out "lorenz-z.svg"
set title 'Lorenz' font 'Liberation Sans Bold,16'
set style line 1 lc rgb '#0060ad' lt 2 lw 2 pt 0 ps 1.0
plot 'lorenz-z.txt' with linespoints ls 1
set out

# y vs x
set key off
set xlabel 'x'
set ylabel 'y'
set terminal svg
set out "lorenz-xy.svg"
set title 'Lorenz' font 'Liberation Sans Bold,16'
set style line 1 lc rgb '#0060ad' lt 2 lw 2 pt 0 ps 1.0
plot 'lorenz-xy.txt' with linespoints ls 1
set out

# z vs y
set key off
set xlabel 'y'
set ylabel 'z'
set terminal svg
set out "lorenz-yz.svg"
set title 'Lorenz' font 'Liberation Sans Bold,16'
set style line 1 lc rgb '#0060ad' lt 2 lw 2 pt 0 ps 1.0
plot 'lorenz-yz.txt' with linespoints ls 1
set out

# z vs x
set key off
set xlabel 'x'
set ylabel 'z'
set terminal svg
set out "lorenz-xz.svg"
set title 'Lorenz' font 'Liberation Sans Bold,16'
set style line 1 lc rgb '#0060ad' lt 2 lw 2 pt 0 ps 1.0
plot 'lorenz-xz.txt' with linespoints ls 1
set out

set terminal svg
set out "lorenz-phase.svg"
splot "lorenz-phase.txt" using 1:2:3 with lines
