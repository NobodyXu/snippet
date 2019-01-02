#!/bin/sh
a=$(dirname "$0")
echo $a
currentDir=$(pwd)
echo $currentDir
realpath="$currentDir/$a/"
echo $realpath
