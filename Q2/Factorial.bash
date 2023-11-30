#!/bin/bash

# Function to calculate factorial
calculate_factorial() {
    num=$1
    factorial=1

    if [ $num -eq 0 ] || [ $num -eq 1 ]; then
        echo "Factorial of $num is 1"
    else
        for ((i=2; i<=num; i++))
        do
            factorial=$((factorial * i))
        done
        echo "Factorial of $num is $factorial"
    fi
}

# Input number from the user
echo "Enter a number:"
read number

calculate_factorial $number
