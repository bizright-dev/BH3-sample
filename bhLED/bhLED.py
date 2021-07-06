# coding: UTF-8

import RPi.GPIO as GPIO
import time

GPIO_LED = 12

# 出力モードに設定
GPIO.setmode(GPIO.BCM)
GPIO.setup(GPIO_LED, GPIO.OUT)

try:
	while 1:

		# 汎用LEDを点灯
		GPIO.output(GPIO_LED, 0)

		# 0.5秒スリープ
		time.sleep(0.5)

		# 汎用LEDを消灯
		GPIO.output(GPIO_LED, 1)

		# 0.5秒スリープ
		time.sleep(0.5)

finally:
	# GPIOの設定をリセット
	GPIO.cleanup()
