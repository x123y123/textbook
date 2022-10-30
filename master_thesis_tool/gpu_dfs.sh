#!/bin/bash
freq=("1109250000" "1058250000" "1007250000" "956250000" "905250000" "854250000" "803250000" "752250000" "701250000" "599250000" "510000000" "408000000" "306000000" "204000000" "114750000")
for i in "${freq[@]}";
do
    echo "$i" > /sys/devices/17000000.gv11b/devfreq/17000000.gv11b/min_freq
    echo "$i" > /sys/devices/17000000.gv11b/devfreq/17000000.gv11b/max_freq
    
    #process path--
    ~/code/main/build/util/util1/mortor_control
    #--------------

done

    echo "$i" > /sys/devices/17000000.gv11b/devfreq/17000000.gv11b/max_freq
    echo "$i" > /sys/devices/17000000.gv11b/devfreq/17000000.gv11b/min_freq
