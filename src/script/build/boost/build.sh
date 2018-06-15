#!/bin/bash
LOG=~/output
TARGET=$2
build() {
    exec ./b2 --prefix=/usr/local	 \
	      --build-dir=/usr/src/boost2\
	      -j 8			 \
	      toolset=clang		 \
	      cflags="-Ofast"		 \
	      cxxflags="-Ofast"		 \
	      variant=release		 \
	      optimization=speed	 \
	      inlining=full		 \
	      threading=multi		 \
	      $TARGET
} > $LOG

cd Down*/*
build
