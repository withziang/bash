#!/bin/bash
# Ziang Wang 261161981
if [[ $# -eq 0 ]]
then
	echo "Error: Task must be specified. Supported tasks: backup, archive, sortedcopy."
	echo "Usage: ./setup.sh <task> <additional_arguments>"
	exit 1
fi

if [[ $1 = "backup" ]]
then 
	# 1
	echo "$(pwd)"
	ls *.txt

	mkdir backup
	cd backup
	echo "Moved to backup directory"
	echo "$(pwd)"

	cp ../*.txt .
	echo "Copied all text files to backup directory"

	echo "Current backup:" > date.txt
	date >> date.txt
	cat date.txt
elif [[ $1 = "archive" ]]
then 
	# 2
	if [[ $# -ne 2 ]]
	then
		echo "Error: Archive task required file format"
		echo "Usage: ./setup.sh archive <fileformat>"
		exit 1
	fi

	archive_name="archive-$(date +'%Y-%m-%d').tgz"
	tar -cvf "$archive_name" *."$2"

	echo "Created archive $archive_name"
	ls -l "$archive_name"
elif [[ $1 = "sortedcopy" ]]
then
	#3
	# additional input
	if [[ $# -ne 3 ]]
	then 
		echo "Error: Expected two additional input parameters."
		echo "Usage: ./setup.sh sortedcopy <sourcedirectory> <targetdirectory>"
		exit 1
	fi

	# if second para is a real dir
	if [[ ! -d $2 ]]
	then
		echo "Error: Input parameter #2 '$2' is not a directory."
		echo "Usage: ./setup.sh sortedcopy <sourcedirectory> <targetdirectory>"
		exit 2
	fi

	# check if the target exits
	if [[ -d $3 ]] 
	then 
		echo "Directory '$3' already exists. Overwrite? (y/n)"
		read ans
		if [[ $ans != "y" ]]
		then 
			echo "Directory not overwritten, Exiting."
			exit 3
		else 
			rm -rf $3
		fi
	fi

	#Create the path
	mkdir $3

	#copy
	c=1
	for f in $(ls -r $2 | sort -r)
	do
		cp -d -r "$2/$f" "$3/$c.$f"
		((c++))
	done
	exit 0

else
	echo "Error: Task must be specified. Supported tasks: backup, archive, sortedcopy."
	echo "Usage: ./setup.sh <task> <additional_arguments>"
	exit 1
fi
