#!/bin/bash

executable="ejecutable\Prueba1"
input_folder="tests\ejercicio1\"
output_folder="out\ejercicio1\"

# Lista de los archivos de prueba
tests=("11.in.txt" "100.in.txt" "1000.in.txt" "10000.in.txt" "100000.in.txt" "1000000.in.txt")

# Para cada prueba, ejecutar el ejecutable y guardar la salida
for t in "${tests[@]}"; do
    echo "Ejecutando prueba $t"
    "$executable" < "$input_folder$t" > "$output_folder/ej2_$t.txt"
done

echo "Todas las pruebas se han ejecutado."
#!/bin/bash

