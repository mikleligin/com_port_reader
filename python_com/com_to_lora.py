import serial
import serial.tools.list_ports

def read_p(port):
    baudrate = 115200
    ser = serial.Serial(port,baudrate=baudrate)
    if ser:
        data = ser.readline()#.decode().strip()
        print(data)
        ser.close()
def write_p(port):
    return

if __name__ == "__main__":
    print("Choose port:")
    i = 0
    ports = serial.tools.list_ports.comports()
    for port in serial.tools.list_ports.comports():
        i+=1
        print(str(i)+". "+str(port))
    inp = 1 #int(input())
    port = str(ports[inp-1]).split(' ')[0]
    print(port)
    read_p(port)