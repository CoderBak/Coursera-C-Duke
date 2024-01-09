#!/bin/bash

emacs=/usr/bin/emacs

# allow one to "git commit" with 1 emacs session open
limit=0
parent=$(readlink /proc/${PPID}/exe)
if [ "$(basename "$parent")" == "git" ]; then
    limit=1
fi

numEmacs=$(pgrep -acf "$emacs")

if [ "$numEmacs" -gt "$limit" ]; then
    echo "Emacs is already running!"
    echo "Return to your previous session with 'fg'."
    echo "Not spawning an additional session."
    exit 1
else
    exec "$emacs" "$@"
fi
