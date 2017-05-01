#!/bin/bash
rm entrega.zip
find . | grep '^\.\/[^\/]*\.\(h\|hpp\|c\|cpp\)$' | zip -@ entrega.zip
