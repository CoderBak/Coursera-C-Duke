#!/bin/bash

git=/usr/bin/git

executeGit() {
    exec "$git" "$@"
}

promptStudent() {
   echo "You specified a git command I didn't expect!"
   echo "Are you sure you want to do this?"
   echo "Enter 'YES' to proceed"
   read -r response

   if [ "$response" == "YES" ]; then
       executeGit "$@"
   fi
   exit 0
}

if [ "$#" -lt 1 ]; then
    executeGit
fi

case $1 in 
    add)
	if [ "$#" -lt 2 ]; then
	    echo "You did not specify a file to add!"
	    echo "usage: git add <filename>"
	    exit 1
	fi
	executeGit "$@"
	;;
    commit)
	executeGit "$@"
	;;
    push)
	executeGit "$@"
	;;
    pull)
	executeGit "$@"
	;;
    status)
	executeGit "$@"
	;;
    remote)
	if [ "$2" == "add" ]; then
           executeGit "$@"
	fi
	
	promptStudent "$@"
	;;
    *)
        promptStudent "$@"
	;;
esac
