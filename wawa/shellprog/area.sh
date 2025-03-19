#!/bin/bash

echo "Enter length: "
read length

echo "Enter width: "
read width

area=$((length * width))
perimeter=$((2 * (length + width)))

echo "Area: $area"
echo "Perimeter: $perimeter"
