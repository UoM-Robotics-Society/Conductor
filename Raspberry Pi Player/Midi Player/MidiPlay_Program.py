import RPi.GPIO as GPIO
import time
import os

Button_Pin = 7

GPIO.setmode(GPIO.BOARD)
GPIO.setup(Button_Pin, GPIO.IN)

count = 0
while count < 1:
        if GPIO.input(Button_Pin):
                text = "aplaymidi -p 128:0 HalloftheMountainKing-FastPart.mid"
                print text
                os.system(text)
                count +=1
        
	
