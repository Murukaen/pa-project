#!/bin/bash

# Calculeaza numarul de linii de cod din toate fisierele .c din directorul curent

echo $(find . -type f -name '*.[ch]' -exec cat '{}' ';'| grep -e '[!-~ ]' | grep -v '^ *$' | grep -v '^ */' | grep -v '^ *\*' | grep -v '^ *{ *' | grep -v '^ *} *' | wc -l )



