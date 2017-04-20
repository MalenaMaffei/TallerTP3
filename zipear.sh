#!/bin/bash

find . | grep '^\.\/[^\/]*\.\(h\|hpp\|c\|cpp\)$' | zip -@ entrega.zip
