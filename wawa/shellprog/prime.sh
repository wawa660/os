echo "Enter a number to check if it's prime: "
read num

if [ $num -lt 2 ]; then
    echo "Not prime"
    exit
fi

for ((i=2; i*i<=$num; i++)); do
    if [ $((num % i)) -eq 0 ]; then
        echo "Not prime"
        exit
    fi
done

echo "Prime"
