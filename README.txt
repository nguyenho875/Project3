En este repositorio se encuentra el desarrollo de un proyecto para el control automático de tranqueras
en mangas. Se incluye en este repositorio todo el firmware desarrollado, un esquemático del hardware
usado, un archivo .apk para la instalación de una aplicación movil necesaria para el uso del sistema,
un video demostrativo dle funcionamiento, y una memoria del desarrollo del trabajo.

Realizado entre abril y julio de 2024 por Augusto Villacampa Horta como trabajo final del seminario
de Sistemas Embebidos de la Facultad de Ingeniería de la Universidad de Buenos Aires.

Consideraciones:

-   En el archivo mbed_app.json se configura el tamaño de los buffers internos de transmisión y
    recepción desde la ESP32, es decir los mensajes que llegan por MQTT y otras configuraciones

-   En el archivo global_defines.h se configuran varios parámetros para el funcionamiento del
    sistema o de los módulos. En el ultimo caso, en los distintos módulos se verifica si estos
    parámetros fueron definidos, y los define si no lo fueron. Esto como medida de seguridad.
