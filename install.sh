#!/bin/bash
mkdir /etc/insomnia
cp font.ttf /etc/insomnia
cp icon.bmp /etc/insomnia
g++ insomnia.cpp -lSDL2 -lSDL2main -lSDL2_ttf -std=c++11 -o /usr/local/bin/insomnia
