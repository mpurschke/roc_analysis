#! /bin/bash

FILE="$1"

if [ -z "$FILE" ] ; then

    root -l roc1.C\(0\)
else

    root -l roc1.C\(\"$FILE\"\)
fi
