#!/bin/bash

PROTOBUFDIR= Directory where protobuf is installed

set -v
set -x
g++ -pthread -std=c++11 -DRCAST_NATIVE -I$PROTOBUFDIR/include/  -o rcast_media_player_x86 *.cxx *.cc *.cpp -lssl -lcrypto -ldl  $PROTOBUFDIR/lib/libprotobuf.a $PROTOBUFDIR/lib/libprotobuf-lite.a -lpthread  
