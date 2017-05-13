#!/bin/bash

user=$1
id=$2
valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 1 < './tests/t0/client0.in'

#valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --show-reachable=yes ./client 127.0.0.1 8080 alumno 1


#./client 127.0.0.1 8080 $user $id
#./client 127.0.0.1 8080 alumno 1 < '/home/male/Taller/3tp/tests/t0/client0.in' 

