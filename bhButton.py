# coding: UTF-8

import RPi.GPIO as GPIO
import time

GPIO_UP = 17
GPIO_DOWN = 27
GPIO_RIGHT = 22
GPIO_LEFT = 24
GPIO_ENTER = 25
BUTTON_SLEEP = 0.05

# ボタンの割込み関数
def gpio_callback(channel):

	# チャタリングによる誤動作防止のため
	# BUTTON_SLEEP(0.05秒)の間隔でGPIOの値を2回取得し
	# 一致する場合のみボタン名を表示
	value1 = GPIO.input(channel)
	if value1 == 1:
		return
	time.sleep(BUTTON_SLEEP)
	value2 = GPIO.input(channel)
	if value2 == 1:
		return
	if value1 != value2:
		return

	if channel == GPIO_UP:
		print('up')
	elif channel == GPIO_DOWN:
		print('down')
	elif channel == GPIO_RIGHT:
		print('right')
	elif channel == GPIO_LEFT:
		print('left')
	elif channel == GPIO_ENTER:
		print('enter')

# 入力モード,PULLUPモードに設定
GPIO.setmode(GPIO.BCM)
GPIO.setup(GPIO_UP, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(GPIO_DOWN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(GPIO_RIGHT, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(GPIO_LEFT, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(GPIO_ENTER, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# GPIOの値の変化(1から0)を検出し、割り込み処理を行う
GPIO.add_event_detect(GPIO_UP, GPIO.FALLING)
GPIO.add_event_detect(GPIO_DOWN, GPIO.FALLING)
GPIO.add_event_detect(GPIO_RIGHT, GPIO.FALLING)
GPIO.add_event_detect(GPIO_LEFT, GPIO.FALLING)
GPIO.add_event_detect(GPIO_ENTER, GPIO.FALLING)
GPIO.add_event_callback(GPIO_UP, gpio_callback)
GPIO.add_event_callback(GPIO_DOWN, gpio_callback)
GPIO.add_event_callback(GPIO_RIGHT, gpio_callback)
GPIO.add_event_callback(GPIO_LEFT, gpio_callback)
GPIO.add_event_callback(GPIO_ENTER, gpio_callback)

while 1:
	time.sleep(1)
