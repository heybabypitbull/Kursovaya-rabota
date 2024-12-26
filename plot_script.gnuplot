set datafile separator ';'
set terminal png size 1200,800
set output 'dependence_graph.png'
set title 'Dependence of Big Integer Exponentiation'
set xlabel 'Calculation length (digits)'
set ylabel 'Time (ns)'
set grid
set style line 1 lc rgb '#FF1493' lw 2 pt 7
set style line 2 lc rgb '#0000CD' lw 2 pt 7
set style line 3 lc rgb '#008000' lw 2 pt 7
plot 'dependence_1.csv' using 1:2 with linespoints linestyle 1 title 'Time (ns) 1','dependence_2.csv' using 1:2 with linespoints linestyle 2 title 'Time (ns) 2', 'dependence_3.csv' using 1:2 with linespoints linestyle 3 title 'Time (ns) 3' 