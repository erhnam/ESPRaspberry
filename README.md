# ESPRaspberry


## Conexión del módulo ESP8266 a Raspberry mediante protocolo MQTT para enviar datos de un LDR.

#### Visión general del proyecto

![](https://github.com/erhnam/ESPRaspberry/blob/master/fotos/Vision.png)

#### Dispositivos:
1. Raspberry Pi Zero W  
2. Módulo ESP8266

#### Sensores utilizados:  

1. LDR

### Programación:

1. Python 3.42
2. Paho-Mqtt
3. Arduino IDE

### Instalación:

Para comenzar, tendremos que actualizar el administrador del panel con una URL personalizada. Abra Arduino, luego vaya a Preferencias (Archivo> Preferencias). A continuación, en la parte inferior de la ventana, copie esta URL en el cuadro de texto "Administrador de directorios adicionales":

Http://arduino.esp8266.com/stable/package_esp8266com_index.json

![](https://github.com/erhnam/ESPRaspberry/blob/master/fotos/adm.png)

Pulse Aceptar. A continuación, vaya al Administrador de la Junta, accediendo a Herramientas> Directorios> Directorios. Debe haber un par de nuevas entradas además de las tablas estándar de Arduino. Busque esp8266. Haga clic en esa entrada, luego seleccione Instalar.

![](https://github.com/erhnam/ESPRaspberry/blob/master/fotos/install.png)

A continuación instale la librería Adafruit MQTT

![](https://github.com/erhnam/ESPRaspberry/blob/master/fotos/mqtt.png)

Finalmente, para instalar el protocolo MQTT en la Raspberry, ejecute el siguiente comando:

sudo pip3 install paho-mqtt python-etcd
