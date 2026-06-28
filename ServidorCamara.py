import socket
import struct
import random # Usamos random para variar la lógica de generación de datos

class ServidorTelemetria:
    def __init__(self, host="127.0.0.1", port=12345):
        self.host = host
        self.port = port

    def _crear_payload(self):
        # En lugar de i % 256, generamos valores aleatorios
        # Esto hace que los datos de prueba sean distintos cada vez
        lecturas = [random.randint(10, 250) for _ in range(768)]
        return struct.pack('768B', *lecturas)

    def ejecutar(self):
        # Inicialización del socket TCP
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as listener:
            listener.bind((self.host, self.port))
            listener.listen()
            print(f"Servidor iniciado en {self.host}:{self.port}")

            # Gestión de la conexión
            cliente_socket, addr = listener.accept()
            with cliente_socket:
                print(f"Conexión recibida desde: {addr}")
                
                # Enviar el paquete de datos
                paquete = self._crear_payload()
                cliente_socket.sendall(paquete)
                print("Transmisión de datos finalizada.")

if __name__ == "__main__":
    servidor = ServidorTelemetria()
    servidor.ejecutar()
