#!/bin/sh
mkdir -p build
cd build
cmake .. && make && make test && make install
