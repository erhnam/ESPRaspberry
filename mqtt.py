# -*- encoding: utf-8 -*- 
import paho.mqtt.client as mqtt

# Llamada para cuando el cliente recibe una respuesta CONNACK desde el servidor.
def on_connect(client, userdata, rc, flags):
	print("Conectado con codigo resultado: " + str(rc))
	# Este topic debe ser el mismo del código del esp
	client.subscribe("/esp/light")

# La llamada cuando un mensaje PUBLISH es recibido desde el servidor.
def on_message(client, userdata, msg):
	#Parsear el dato recibido y hacer casting a entero
	dato = int(str(msg.payload).replace("'" , '').replace("b", ''))

	#Jugar con el dato recibido
	if dato > 800:
		print("Hay mucha luz")
	elif dato > 600 and dato <= 800:
		print("Hay luz")
	elif dato > 300  and dato <= 600:
		print("Hay poca luz")
	else:
		print("No hay luz")

client = mqtt.Client()

client.on_connect = on_connect

client.on_message = on_message

client.connect("localhost", 1883, 60)

client.loop_forever()
