#!/bin/bash

# This wrapper script for gdb is a work in progress. Previously, Coursera was
# running a version of Docker that blocks ptrace unless the `--cap-add=SYS_PTRACE`
# run flag is used (which Coursera declined to do). To work around this restriction,
# we were attempting to use gdb through valgrind instead of ptrace. We had yet to
# solve the problem of capturing I/O for valgrind when using gdb within emacs.

# Fortunately for us, Coursera recently upgraded to a version of Docker that
# relaxes the ptrace restrictions. We are going to keep this wrapper script in
# the project in a disabled state should we suddenly need it in the future.

# echo "args are $@ "
prog="${*: -1}"
if [ "$prog" == "" ]
then
    echo "You must specify a program on the command line for this gdb setup"
    exit 1
fi
base=$(basename "$prog")
dir=$(dirname "$prog")
fullprog="${dir}/${base}"
# echo "full prog is $fullprog"
cat
valgrind --vgdb=full --vgdb-error=0 "$fullprog"  &
VALGRINDPID=$!
ps ax |grep valgrind
cat > ~/.gdbinit << EOF
target remote | /usr/bin/vgdb  --pid=$VALGRINDPID
break main
continue
EOF
args=( "$@" )
# echo "args are $args"
unset "args[${#args[@]}-1]"
# echo "Now args are $args"
/usr/bin/gdb "${args[@]}"
kill -9 $VALGRINDPID
