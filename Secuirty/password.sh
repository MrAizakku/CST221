#!/bin/bash
echo "Password : '$1'"
len="${#1}"
count='0'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

if test $len -ge 8 ; then
	echo -e "Password Length : ${GREEN}Ok${NC}"
	count=$((count + 1))
else
	echo -e "Password Length : ${RED}NOT OKAY!${NC}"
fi
echo "$1" | grep -q [0-9]
if test $? -eq 0 ; then
	echo -e "Password Contains Number(s) : ${GREEN}Ok${NC}"
	count=$((count + 1))
else
	echo -e "Password Contains Number(s) : ${RED}NO!${NC}"
fi	
echo "$1" | grep -q [A-Z]
if test $? -eq 0 ; then
	echo -e "Password Contains Capital Letter(s) : ${GREEN}Ok${NC}"
	count=$((count + 1))
else
	echo -e "Password Contains Capital Letter(s) : ${RED}NO!${NC}"
fi	
echo "$1" | grep -q [a-z]
if test $? -eq 0 ; then
	echo -e "Password Contains Lower Letter(s) : ${GREEN}Ok${NC}"
	count=$((count + 1))
else 
	echo -e "Password Contains Lower Letter(s) : ${RED}NO!${NC}"
fi
echo "$1" | grep -q "[@\#$%&\*-\=]"
if test $? -eq 0 ; then
	echo -e "Password Contains Symbol(s) : ${GREEN}Ok${NC}"
	count=$((count + 1))
else
	echo -e "Password Contains Symbol(s) : ${RED}NO!${NC}"
fi
if [ $count == 5 ] ; then
	echo -e "'$1' is an ${GREEN}okay ${NC}Password"
else	
	echo -e "'$1' is ${RED}NOT an okay ${NC}Password"
fi
