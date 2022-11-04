reset
set title 'power of board system'
#set title 'gyro freq power'
set xlabel 'cpufreq (kHz)'

#set ylabel 'time'
set ylabel 'variation ratio'

set term png enhanced font 'Times_New_Roman,10'

#set output "time freq in gpsthread.png"
set output "variation.png"

set format x '%10.0f'
set xtic 100000
set xtics rotate by 45 right


plot [100000:2000000][0:1]"./fix_gpu_956250000/gyro.txt"using 2:5 with linespoints title 'g956250000',\
