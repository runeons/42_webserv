#!/usr/bin/env zsh

clean_str()
{
  tmp=$1
  # remove potential final '+'
  length=${#tmp}
  ((length--))
  if [[ $tmp[$length] == "+" ]]; then
    tmp=${tmp[0,length-1]}
    length=${#tmp}
  fi
  # remove final letter representing the size: K,M,G,etc
  tmp=${tmp[0,length-1]}
  echo $tmp
}

echo "" > $2
echo "command,memory_usage" >> $2
for (( i = 0; i < $1; i++ )); do
  MEM=$(clean_str `top -stats command,mem -l 1 | grep webserv | cut -c18-`)
  printf "[ %5d ] %s\n" $i $MEM
  printf "%s,%s\n" "webserv" $MEM >> $2
  sleep 0.1
done

cat $2
