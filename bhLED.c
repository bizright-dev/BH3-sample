#include <stdio.h>
#include <wiringPi.h>

#define GPIO_LED 12

int setupGpio();

// メイン関数
int main(int argc, char *argv[]) {

	// GPIOの初期化
	if (setupGpio() == -1) return 1;

	while (1) {

		// 汎用LEDを点灯
		digitalWrite(GPIO_LED, 0);

		// 0.5秒スリープ
        	delay(500);

		// 汎用LEDを消灯
        	digitalWrite(GPIO_LED, 1);

		// 0.5秒スリープ
        	delay(500);

	}
	return 0;
}

// GPIOの初期化関数
int setupGpio() {
	// WiringPiの初期化
	if (wiringPiSetupGpio() == -1) return -1;

	// 出力モードに設定 
	pinMode(GPIO_LED, OUTPUT);

	return 0;
}
