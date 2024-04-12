#!/bin/ksh
#
echo "Old User = " `env | grep ^USR_KEY`
export USR_KEY=$1
export SHR_USR_KEY=$1\0000
export SHR_USR_KEYS=$1\1000
echo "New User = " `env | grep ^USR_KEY`
