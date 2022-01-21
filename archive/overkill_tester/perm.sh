#!/usr/bin/env zsh
for (( i = 0; i <= 7; i++ )); do
	for (( j = 0; j <= 7; j++ )); do
		for (( k = 0; k <= 7; k++ )); do
			echo "this is file_$i$j$k" > $1/file_$i$j$k; chmod $i$j$k $1/file_$i$j$k;
		done
	done
done
