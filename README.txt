Consideraciones:

-   En el archivo mbed_app.json se configura el tamaño de los buffers internos de transmisión y
    recepción desde la ESP32, es decir los mensajes que llegan por MQTT y otras configuraciones

-   En el archivo global_defines.h se configuran varios parámetros para el funcionamiento del
    sistema o de los módulos. En el ultimo caso, en los distintos módulos se verifica si estos
    parámetros fueron definidos, y los define si no lo fueron. Esto como medida de seguridad.