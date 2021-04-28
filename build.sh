#!/bin/bash -e

mkdir -p out
rm -rf out/*

cmake -GNinja -B out .
ninja -C out

rm -rf out
