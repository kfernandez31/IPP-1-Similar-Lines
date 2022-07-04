#!/bin/bash

#makra na kolor tekstu
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

#sprawdzenie ilości podawanych argumentów
if [ "$#" -ne 2 ]
then
    echo -e "${RED}ERROR: wrong number of parameters. Please provide: 1) executable name 2) testing directory${NC}";
    exit 1;
fi

prog=$1;
dir=$2;

#sprawdzenie poprawności argumentów
if [[ ! -x "$prog" ]]
then
  echo -e "${RED}ERROR: Wrong executable name${NC}"
  exit 1
fi

if [[ ! -d "$dir" ]]
then
  echo -e "${RED}ERROR: Wrong testing directory${NC}"
  exit 1
fi

#uruchamianie testów
for i in "$dir"/*.in; do 
  ./"$prog" < "$i" > "res.out" 2> "res.err"
  valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./"$prog" < "$i" >/dev/null 2>/dev/null
  #./"$prog" < "$i" >/dev/null 2>/dev/null
  if [ $? -ne 0 ]
  then
      echo -e "${RED}$i - Test failure: memory issues${NC}"
  else
      diff "res.out" "${i%in}out" && diff "res.err" "${i%in}err";
      if [ $? -ne 0 ]
      then
          echo -e "${RED}$i - Test failure: wrong output${NC}";
      else
          echo -e "${GREEN}$i - Test success${NC}";
      fi
  fi

#kasowanie plików tymczasowych
rm res.out res.err
done