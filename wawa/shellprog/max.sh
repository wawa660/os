read -p "Enter 3 numbers: " a b c
echo $((a>b?(a>c?a:c):(b>c?b:c)))
