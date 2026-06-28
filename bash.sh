#!/usr/bin/env bash

PYTHON_SERVER="ServidorCamara.py"
BINFILE="./cliente"

# Comprobamos que los archivos existen y tienen permisos de ejecución
[[ ! -f "$BINFILE" ]] && echo "El archivo $BINFILE no existe, saliendo del programa" >&2 && exit 1
[[ ! -x "$BINFILE" ]] && echo "El archivo $BINFILE no tiene permisos de ejecución, saliendo del programa" >&2 && exit 1
[[ ! -f "$PYTHON_SERVER" ]] && echo "El archivo $PYTHON_SERVER no existe, saliendo del programa" >&2 && exit 1
[[ ! -x "$PYTHON_SERVER" ]] && echo "El archivo $PYTHON_SERVER no tiene permisos de ejecución, saliendo del programa" >&2 && exit 1

echo "[1/3] Iniciando el servidor Python ($PYTHON_SERVER)..."
python3 "$PYTHON_SERVER" &
PID=$! # Guardamos el PID del proceso
sleep 3

echo "[2/3] Ejecutando el cliente C++..."
$BINFILE

echo "[3/3] Cerrando el servidor Python (PID: $PID)..."
wait "$PID"
if kill -0 "$PID" 2> /dev/null
then
    kill "$PID"
    echo "Deteniendo proceso (pid=$PID)"
fi
