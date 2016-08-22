#!/bin/sh

g++ Tradio.cpp Serial.cpp `pkg-config gtkmm-2.4 --libs --cflags libusb-1.0` -o tradio.out
./tradio.out
