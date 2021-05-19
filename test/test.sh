cd ./test

echo "Test help command:"
../autcel -h
echo " "

echo "Test version command:"
../autcel -V
echo " "

echo "Test 30 rule: "
../autcel 30 80 inicial_30_80 -o evolucion_30_80