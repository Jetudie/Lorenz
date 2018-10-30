reset
set title "Error"
set xlabel "Times"
set ylabel "e"
set key left
set grid
set term png enhanced font 'Verdana, 12'
set output "error.png"
set xrange [:]
set yrange [:]
plot \
"log.txt" using 1:2 title "e1" lc rgb "red", \
"log.txt" using 1:3 title "e2" lc rgb "green", \
"log.txt" using 1:4 title "e3" lc rgb "blue"

set title "State x_m"
set xlabel "Times"
set ylabel "Value"
set output "state.png"
plot \
"log.txt" using 1:5 title "x1m" lc rgb "red", \
"log.txt" using 1:6 title "x2m" lc rgb "green", \
"log.txt" using 1:7 title "x3m" lc rgb "blue"
reset