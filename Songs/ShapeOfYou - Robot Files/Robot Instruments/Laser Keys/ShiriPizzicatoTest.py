#Ed Sheeran' Shape of You

import pygame.midi      #import midi library
import time             #import time library
import RPi.GPIO as GPIO #import GPIO library
GPIO.setmode(GPIO.BCM)  #Set GPIO to BCM pins
GPIO.setwarnings(False) #Turn off warning flags
pygame.midi.init()      #Initialise midi files
player = pygame.midi.Output(0) #Choice of instrument

Laser1 = 21
Laser2 = 26
Laser3 = 20
Laser4 = 13
Laser5 = 16
Laser6 = 12
Laser7 = 5
Laser8 = 6
Laser9 = 22
Laser10 = 27
Laser11 = 18
Laser12 = 17
Laser13 = 4
Laser14 = 25 #Laser number = pin number

GPIO.setup(Laser1,GPIO.OUT)
GPIO.setup(Laser2,GPIO.OUT)
GPIO.setup(Laser3,GPIO.OUT)
GPIO.setup(Laser4,GPIO.OUT)
GPIO.setup(Laser5,GPIO.OUT)
GPIO.setup(Laser6,GPIO.OUT)
GPIO.setup(Laser7,GPIO.OUT)
GPIO.setup(Laser8,GPIO.OUT)
GPIO.setup(Laser9,GPIO.OUT)
GPIO.setup(Laser10,GPIO.OUT)
GPIO.setup(Laser11,GPIO.OUT)
GPIO.setup(Laser12,GPIO.OUT)
GPIO.setup(Laser13,GPIO.OUT)
GPIO.setup(Laser14,GPIO.OUT)
#Set lasers as outputs

GPIO.output(Laser5, GPIO.HIGH)
player.note_on(61, 127)         #61

time.sleep(0.46875)        

GPIO.output(Laser13, GPIO.HIGH)
player.note_on(76, 127)         #76 
GPIO.output(Laser11, GPIO.HIGH)
player.note_on(73, 127)         #73

time.sleep(0.46875) 

GPIO.output(Laser5, GPIO.LOW)
player.note_off(61, 127)         #61 off

time.sleep(0.3125)

GPIO.output(Laser1, GPIO.HIGH)
player.note_on(54, 127)         #54

time.sleep(0.0390625)

GPIO.output(Laser13, GPIO.LOW)
player.note_off(76, 127)        #76 off

time.sleep(0.0390625)

GPIO.output(Laser11, GPIO.LOW)
player.note_off(73, 127)       #73 off 

time.sleep(0.390625)

GPIO.output(Laser11, GPIO.HIGH)
player.note_on(73, 127)

GPIO.output(Laser14, GPIO.HIGH)
player.note_on(78, 127) 

time.sleep(0.5859375)

GPIO.output(Laser1, GPIO.LOW)
player.note_off(54, 127) 

time.sleep(0.1953125)

GPIO.output(Laser2, GPIO.HIGH)
player.note_on(57, 127) 

time.sleep(0.0390625)

GPIO.output(Laser14, GPIO.LOW)
player.note_off(78, 127) 
GPIO.output(Laser11, GPIO.LOW)
player.note_off(73, 127) 

time.sleep(0.4296875)

GPIO.output(Laser6, GPIO.HIGH)
player.note_on(69, 127) 

GPIO.output(Laser11, GPIO.HIGH)
player.note_on(73, 127)

time.sleep(0.625)

GPIO.output(Laser2, GPIO.LOW)
player.note_off(57, 127) 

time.sleep(0.15625)

GPIO.output(Laser3, GPIO.HIGH)
player.note_on(59, 127)

time.sleep(0.078125)

GPIO.output(Laser6, GPIO.LOW)
player.note_off(69, 127) 

time.sleep(0.0390625)

GPIO.output(Laser11, GPIO.LOW)
player.note_off(73, 127)

time.sleep(0.3515625)

GPIO.output(Laser12, GPIO.HIGH)
player.note_on(75, 127)

GPIO.output(Laser7, GPIO.HIGH)
player.note_on(71, 127)

time.sleep(0.703125)

GPIO.output(Laser3, GPIO.LOW)
player.note_off(59, 127)

time.sleep(0.078125)

GPIO.output(Laser12, GPIO.HIGH)
player.note_on(75, 127)

GPIO.output(Laser5, GPIO.HIGH)
player.note_on(61, 127)         #61

time.sleep(0.0390625)

GPIO.output(Laser7, GPIO.LOW)
player.note_off(71, 127)

time.sleep(0.4296875)

GPIO.output(Laser13, GPIO.HIGH)
player.note_on(76, 127)         #76 
GPIO.output(Laser11, GPIO.HIGH)
player.note_on(73, 127)         #73

time.sleep(0.5859375)

GPIO.output(Laser5, GPIO.LOW)
player.note_off(61, 127)         #61

time.sleep(0.1953125)

GPIO.output(Laser13, GPIO.LOW)
player.note_off(76, 127)         #76 

GPIO.output(Laser1, GPIO.HIGH)
player.note_on(54, 127)         #54

time.sleep(0.0390625)

GPIO.output(Laser11, GPIO.LOW)
player.note_off(73, 127)         #73

time.sleep(0.4296875)

GPIO.output(Laser14, GPIO.HIGH)
player.note_on(78, 127)         #78 
GPIO.output(Laser11, GPIO.HIGH)
player.note_on(73, 127)         #73

time.sleep(0.625)

GPIO.output(Laser1, GPIO.LOW)
player.note_off(54, 127)         #54

time.sleep(0.15625)

GPIO.output(Laser11, GPIO.LOW)
player.note_off(73, 127)         #73

GPIO.output(Laser2, GPIO.HIGH)
player.note_on(57, 127)         #57

time.sleep(0.0390625)

GPIO.output(Laser14, GPIO.LOW)
player.note_off(78, 127)         #78 

time.sleep(0.4296875)

GPIO.output(Laser11, GPIO.HIGH)
player.note_on(73, 127)         #73

GPIO.output(Laser6, GPIO.HIGH)
player.note_on(69, 127) 

time.sleep(0.5859375)

GPIO.output(Laser2, GPIO.LOW)
player.note_off(57, 127)         #57

time.sleep(0.1953125)

GPIO.output(Laser6, GPIO.LOW)
player.note_oFF(69, 127) 

GPIO.output(Laser3, GPIO.HIGH)
player.note_on(59, 127) 

time.sleep(0.0390625)

GPIO.output(Laser11, GPIO.LOW)
player.note_off(73, 127)

time.sleep(0.4296875)

GPIO.output(Laser7, GPIO.HIGH)
player.note_on(71, 127) 

GPIO.output(Laser6, GPIO.HIGH)
player.note_on(66, 127) 

time.sleep(0.703125)

GPIO.output(Laser3, GPIO.LOW)
player.note_off(59, 127) 

GPIO.output(Laser6, GPIO.LOW)
player.note_off(66, 127) 

GPIO.output(Laser7, GPIO.LOW)
player.note_off(71, 127) 



GPIO.cleanup()      #Cleans GPIO

