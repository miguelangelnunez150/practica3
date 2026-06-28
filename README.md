# Práctica 3: Implementación de Sockets TCP/IP en C++

## 1. Objetivo del Proyecto
Desarrollo de una arquitectura cliente-servidor orientada a la adquisición y persistencia de datos térmicos. Este sistema garantiza la comunicación entre procesos locales mediante el protocolo TCP/IP, utilizando C++ como lenguaje base para el procesamiento y Python para el despliegue del servicio.

---

## 2. Mapa del Repositorio
El proyecto sigue una organización modular para facilitar la escalabilidad y el mantenimiento del código:

```text
bash.sh                  # Orquestador de despliegue y compilación
cliente.cpp              # Lógica del cliente TCP (implementación C++)
ServidorCamara.py        # Servicio simulador (Python 3)
resultados.txt           # Reporte generado por el cliente
LICENSE                  # Términos de uso (MIT)
README.md                # Documentación del proyecto
```

## 3. Entorno de Ejecución
- El sistema ha sido validado bajo las siguientes especificaciones técnicas:
- Sistema: Entorno Linux (distribuciones basadas en Debian/Ubuntu).
- Compilador: g++ (Standard C++11 o superior).
-Dependencias: Intérprete python3 para la ejecución del servidor.

---

## 4. Guía de Puesta en Marcha
Para ejecutar el entorno, asegúrate de tener permisos de escritura en la carpeta. Utiliza el orquestador proporcionado:
# Otorgar permisos de ejecución al script
```bash
chmod +x bash.sh
```
---

# Desplegar el pipeline de red
```bash
./bash.sh
```
## 5. Notas Técnicas
Gestión de Sockets: El cliente implementa un cierre seguro para evitar el bloqueo del puerto 12345 en ejecuciones consecutivas.

Persistencia: Los datos recibidos se procesan y almacenan automáticamente en el archivo resultados.txt.

## 6. Información de Autoría
- Estudiante: Miguel Ángel Núñez Cózar
## 7. Licencia
Proyecto distribuido bajo la licencia MIT License.
