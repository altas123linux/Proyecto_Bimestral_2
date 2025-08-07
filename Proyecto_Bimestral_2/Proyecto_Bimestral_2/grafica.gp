set title 'Solucion Grafica del Problema de Optimizacion - Flair Furniture'
set xlabel 'x1 (Numero de mesas)'
set ylabel 'x2 (Numero de sillas)'
set grid
set xrange [0:60]
set yrange [0:50]
set style line 1 lc rgb 'red' lw 2
set style line 2 lc rgb 'blue' lw 2
set style line 3 lc rgb 'green' lw 2
set style line 4 lc rgb 'purple' lw 2
set style line 5 lc rgb 'orange' lw 2
plot (80 + -1.33333*x) with lines linestyle 1 title 'Carpinteria: 4x1 + 3x2 <= 240', (100 + -2*x) with lines linestyle 2 title 'Pintura: 2x1 + x2 <= 100', (60 + -0*x) with lines linestyle 3 title 'Inventario sillas: x2 <= 60', '-' with points pointtype 7 pointsize 2 lc rgb 'black' title 'Punto Optimo'
0 80
e
set object 1 polygon from 0,0 to 0,100 to 0,80 to 60,0 to 0,0
set object 1 fillstyle solid 0.2 fillcolor 'yellow'
replot
pause -1
