# Imagenes en Pantalla OLED SSD1306 con ESP32/Arduino ===

## Requisitos
- VSCode 
- Platformio
- Librería en Platformio: Adafruit SSD1306 por Adafruit
- Cable USB adecuado
- Placa ESP32/Arduino
- Pantalla OLED SSD1306
- Protoboard
- Cables de conexión

## Insatalación
1. Instalar VSCode con la extensión Platformio
2. Clonar el repositorio de Github:
   1. Copiar la URL del repositorio
   2. Abrir VSCode
   3. Seleccionar "Terminal" en la barra de menú
   4. Escribir `git clone <URL>` y presionar Enter
3. Cambiar la tarjeta especificada en 'platformio.ini' por la del usuario
    - Por ejemplo para un Arduino UNO el archivo platformio.ini debería verse así:
    ``
    [env:uno]
    platform = atmelavr
    board = uno
    framework = arduino
    lib_deps = 
      adafruit/Adafruit SSD1306@^2.5.15
    ``
4. Compilar el programa

## Uso
1. Una vez la tarjeta sea especificada en "platformio.ini" de ser necesario cambiar los pines para el LED y los pines SDA y SCL de I2C
2. Cargar el programa
3. Abrir el monitor serial 
4. En el monitor serial escribir "IMG>AXL10" para mostrar la imagen en pantalla OLED SSD1306 (Esto muestra la imagen de un Ajolote por 10 segundos), utilizar las imagenes precargadas del programa o cargar una imagen con el método del video del proyecto. Parte 1 -> [https://youtu.be/T3HwaMLArIo] Parte 2 -> []

## Tecnologías
- C++
- PlatformIO

## Licencia
Este proyecto está bajo la Licencia MIT. ===

## Autor
- Mexatrónica ===
