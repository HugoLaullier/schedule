set term png
set output "schedule.png"
set xrange[0:915000]
set xlabel "Number of Evaluations"
set ylabel "Fitness"
plot 'schedule.dat' using 3:4 t 'Best Fitness' w lines, 'schedule.dat' using 3:5 t  'Average' w lines, 'schedule.dat' using 3:6 t 'StdDev' w lines
