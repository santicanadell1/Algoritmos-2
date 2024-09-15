@echo off
set executable=ejecutables/ejercicio2.exe
set input_folder=tests/ejercicio2/
set output_folder=out/ejercicio2/

:: Lista de los archivos de prueba
set tests=11.in.txt 100.in.txt 1000.in.txt 10000.in.txt 100000.in.txt 1000000.in.txt

:: Para cada prueba, ejecutar el ejecutable y guardar la salida
for %%t in (%tests%) do (
    echo Ejecutando prueba %%t
    %executable% < %input_folder%%%t > %output_folder%ej2_%%t.txt
)

echo Todas las pruebas se han ejecutado.
pause