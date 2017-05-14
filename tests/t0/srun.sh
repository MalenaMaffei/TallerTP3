#!/bin/bash

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./server 8080 usuarios.txt materias.txt
#./server 8083 tests/t0/usuarios.txt tests/t0/materias.txt

