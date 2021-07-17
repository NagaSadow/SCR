#!/bin/bash

export LC_ALL=C
echo "Nowa zmiana"
dzien_tyg=$(date +%u)

if [ $dzien_tyg -gt 5 ]
then
    echo "Dzisiaj jest dzień świąteczny!"
else
    echo "Dzisiaj jest dzień roboczy..."
fi
