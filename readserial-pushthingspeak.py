import serial
import httplib2
import re

#Ask COM port number
comport = raw_input('Serial port? COM')
try:
    comport = int(comport)
except ValueError:
    print("Fill it with number only. For port COMX, please input X")
    exit()
arduino = serial.Serial('COM'+str(comport), 115200, timeout=1)
while True:
        data = arduino.readline() #[:-2]
        if data:
                print data
                matchObj = re.match( r'-(.+):(.+)-', data, re.M|re.I) #Data format received from Arduino:  -suhu:kelembapan-
                if matchObj:
                        print "Read data format : ", matchObj.group()
                        print "Temperature : ", matchObj.group(1)
                        print "Humidity : ", matchObj.group(2)
                        thingspeakAPI = "https://api.thingspeak.com/update?api_key=<YOUR API KEY HERE>"+"&field1="+matchObj.group(1)+"&field2="+matchObj.group(2)
                        resp, content = httplib2.Http().request(thingspeakAPI)
                        print thingspeakAPI
                        print resp.status
                else:
                   print "Unable to read data format."

