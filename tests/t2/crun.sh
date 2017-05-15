#!/bin/bash

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 1 < 'client0.in'
echo '---esperado: ----'
cat 'client0.out'

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 docente 57 < 'client1.in'
echo '---esperado: ----'
cat 'client1.out'
