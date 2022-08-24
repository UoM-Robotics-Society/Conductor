#Ed Sheeran' Shape of You

import pygame.midi      #import midi library
import time             #import time library
import RPi.GPIO as GPIO #import GPIO library
import os



On_Button = 7

GPIO.setmode(GPIO.BOARD)
GPIO.setup(On_Button, GPIO.IN, GPIO.PUD_DOWN)

count = 0
while True:
    if GPIO.input(On_Button):
        text = "aplay /home/pi/Desktop/ShapeOfYou_PizziStrings.wav"
        print text
        os.system(text)
        if count == 2:
            os.system(text)
            count = 0
        count+=1



GPIO.cleanup()      #Cleans GPIO

