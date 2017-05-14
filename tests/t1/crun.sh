#!/bin/bash

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 8 < 'client0.in'
echo '---esperado: ----'
cat 'client0.out'

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 1 < 'client1.in'
echo '---esperado: ----'
cat 'client1.out'

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 2 < 'client2.in'
echo '---esperado: ----'
cat 'client2.out'

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 3 < 'client3.in'
echo '---esperado: ----'
cat 'client3.out'

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 4 < 'client4.in'
echo '---esperado: ----'
cat 'client4.out'

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 5 < 'client5.in'
echo '---esperado: ----'
cat 'client5.out'

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 6 < 'client6.in'
echo '---esperado: ----'
cat 'client5.out'

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 7 < 'client7.in'
echo '---esperado: ----'
cat 'client7.out'

valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 9 < 'client8.in'
echo '---esperado: ----'
cat 'client8.out'

