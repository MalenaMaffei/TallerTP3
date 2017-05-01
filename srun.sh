#!/bin/bash

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./server 8080 tests/t3/usuarios.txt tests/t3/materias.txt
#./server 8080 tests/mio1/usuarios.txt tests/mio1/materias.txt

