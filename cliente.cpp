#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>

using namespace std;

// Abre el socket
int abrir_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cerr << "Error: No se pudo crear el socket." << endl;
    }
    return sock;
}

// Configura la IP y el puerto
struct sockaddr_in preparar_direccion(const char* ip_host, int puerto_host) {
    struct sockaddr_in dir;
    dir.sin_family = AF_INET;
    dir.sin_port = htons(puerto_host);

    // Pasa la IP a binario
    if (inet_pton(AF_INET, ip_host, &dir.sin_addr) <= 0) {
        cerr << "Error: IP no valida." << endl;
    }
    return dir;
}

// Conecta con el servidor remoto
bool conectar_al_host(int sock_fd, struct sockaddr_in dir_servidor) {
    cout << "Conectando al servidor..." << endl;
    if (connect(sock_fd, (struct sockaddr*)&dir_servidor, sizeof(dir_servidor)) == -1) {
        cerr << "Error: Conexion fallida." << endl;
        return false;
    }
    cout << "Conectado con exito." << endl;
    return true;
}

// Lee los bytes enviados por el servidor
vector<float> leer_temperaturas(int sock_fd) {
    vector<float> lista_valores;
    unsigned char buffer_lectura;

    cout << "Leyendo valores..." << endl;
    // Recibe los datos uno a uno hasta terminar
    while (recv(sock_fd, &buffer_lectura, sizeof(buffer_lectura), 0) > 0) {
        lista_valores.push_back(static_cast<float>(buffer_lectura));
    }
    return lista_valores;
}

// Guarda los datos en el archivo de texto
void volcar_a_fichero(const vector<float>& valores, const string& ruta_archivo) {
    ofstream archivo(ruta_archivo);

    if (!archivo.is_open()) {
        cerr << "Error: No se abrio el archivo " << ruta_archivo << endl;
        return;
    }

    // Escribe cada valor en una linea nueva
    for (size_t i = 0; i < valores.size(); i++) {
        archivo << valores[i] << endl;
    }

    archivo.close();
    cout << "Archivo guardado: " << ruta_archivo << endl;
}

// Muestra los datos por consola
void mostrar_datos(const vector<float>& valores) {
    cout << "\nDATOS RECIBIDOS" << endl;
    for (size_t i = 0; i < valores.size(); i++) {
        cout << "Muestra " << i << ": " << valores[i] << endl;
    }
    cout << "=======================" << endl;
    cout << "Total de muestras: " << valores.size() << endl;
}

int main() {
    const char* SERVER_IP = "127.0.0.1";
    const int SERVER_PORT = 12345;

    cout << "CLIENTE DE SENSOR TERMICO" << endl;

    // 1. Crear socket
    int mi_socket = abrir_socket();
    if (mi_socket == -1) return 1;

    // 2. Preparar datos de red
    struct sockaddr_in config_red = preparar_direccion(SERVER_IP, SERVER_PORT);

    // 3. Establecer conexion
    if (!conectar_al_host(mi_socket, config_red)) {
        close(mi_socket);
        return 1;
    }

    // 4. Descargar informacion
    vector<float> temperaturas = leer_temperaturas(mi_socket);

    if (temperaturas.empty()) {
        cout << "No hay datos para procesar." << endl;
    }
    else {
        // 5. Guardar e imprimir
        volcar_a_fichero(temperaturas, "Resultados.txt");
        mostrar_datos(temperaturas);
    }

    // 6. Cerrar socket y salir
    close(mi_socket);
    cout << "Socket cerrado. Fin." << endl;

    return 0;
}