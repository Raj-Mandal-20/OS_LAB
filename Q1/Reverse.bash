#!/bin/bash

# Function to reverse the number
reverse_number() {
    num=$1
    reverse=0

    while [ $num -gt 0 ]
    do
        remainder=$((num % 10))
        reverse=$((reverse * 10 + remainder))
        num=$((num / 10))
    done

    echo "Reversed number: $reverse"
}

# Input number from the user
echo "Enter a number:"
read number

reverse_number $number
