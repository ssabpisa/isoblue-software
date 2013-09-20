#!/bin/bash
#

if (( $# < 1 ))
	then echo "Usage: query.sh <timeoffset>"
	exit
fi

while read line
do
	k=$(date +%s)
	((k=k-$1))
	ts=$(echo $line | grep -o "[0-9]*\.")
	tts=${ts:0:10}
	if (( $tts >= $k ))
		then echo $line
	fi
done < sample_dump.txt