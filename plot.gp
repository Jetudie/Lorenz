reset
set title "Error"
set xlabel "Times"
set ylabel "e"
set key left
set grid
set term png enhanced font 'Verdana, 12'
set output "test.png"
pl [:] [:] \
"log.txt" using 1:2 title "e1" lc rgb "red", \
"log.txt" using 1:3 title "e2" lc rgb "green", \
"log.txt" using 1:4 title "e3" lc rgb "blue"
reset