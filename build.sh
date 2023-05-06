#!/bin/sh

H=/home/qmk_firmware
TARGETS="default nomsc"
FOLDER=keyboards/tadakado/tk46v4/firm/0.11.0/uf2

cd $H

for target in $TARGETS; do
    echo $target
    make tk46v4:${target}:uf2 && cp .build/tk46v4_${target}.uf2 $FOLDER
done

