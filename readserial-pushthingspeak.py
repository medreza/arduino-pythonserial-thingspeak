import serial
import httplib2
import re

arduino = serial.Serial('COM6', 115200, timeout=1)
while True:
        data = arduino.readline() #[:-2] the last bit gets rid of the new-line chars
        if data:
                print data
                resp, content = httplib2.Http().request("127.0.0.1")
                print resp.status
                matchObj = re.match( r'-(.+):(.+)-', data, re.M|re.I) #-234:654-
                if matchObj:
                   print "Read data format : ", matchObj.group()
                   print "Temperature : ", matchObj.group(1)
                   print "Humidity : ", matchObj.group(2)
                else:
                   print "Unable to read data format."

