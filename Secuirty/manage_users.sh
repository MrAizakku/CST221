#!/bin/bash
file="$1"; group="$2"; operation="$3"
RED='\033[0;31m'; GREEN='\033[0;32m'; NC='\033[0m'
if [[ -z "$1" || -z "$2" || -z "$3" ]]; then
	echo -e "${RED}Invalid Inputs.${NC}"
else
	if [ $(id -u) -eq 0 ]; then
		if [ "$3" == "add" ]; then
			if grep -q $group /etc/group ; then
				echo -e "${RED} $group group already exists!${NC}"
			else
				echo -e "${GREEN}$group group added.${NC}"; groupadd $group
			fi
			while read -r user pass; do
				name="$user"; word="$pass"
				echo "  Username : '$name'"; echo "  Password : '$word'"
				egrep "^$name" /etc/passwd >/dev/null
				if [ $? -eq 0 ]; then
					echo -e "${RED}$name already exists.${NC}"
				else
					useradd -m -p $word $name
					[ $? -eq 0 ] && echo -e "${GREEN}User $name has been added to $group group.${NC}" || echo -e "${RED}Proces failed.${NC}"
				fi
				sudo usermod -a -G $group $name
			done < "$file"
		fi

		if [ "$3" == "remove" ]; then
			while read -r user pass; do
				name="$user"; word="$pass"
				userdel -r $name
			done < "$file"
			
			if grep -q $group /etc/group; then
				groupdel $group
				echo -e "${GREEN} $group group deleted.${NC}"
			else
				echo -e "${RED} $group group doesn't exist!${NC}"
			fi
		fi
	else
		echo -e "${RED}You do not have access.${NC}"; exit 2
	fi			
fi
