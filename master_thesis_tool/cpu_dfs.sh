#!/bin/bash
freq=("1907200" "1881600" "1804800" "1728000" "1651200" "1574400" "1497600" "1420800" "1344000" "1267200" "1190400" "1113600" "1036800" "960000" "883200" "806400" "729600" "652800" "576000" "499200" "422400" "345600" "268800" "192000" "115200")
for i in "${freq[@]}";
do
    echo "$i" > /sys/devices/system/cpu/cpu*/cpufreq/scaling_max_freq
    
    #process path--
    ~/code/main/build/util/util1/mortor_control
    #--------------

done

    echo "$i" > /sys/devices/system/cpu/cpu*/cpufreq/scaling_max_freq
