#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>

#define GPIO_UP 17
#define GPIO_DOWN 27
#define GPIO_RIGHT 22
#define GPIO_LEFT 24
#define GPIO_ENTER 25
#define BUTTON_USLEEP 50000
#define RESET_SEC 5

int setupGpio();
void isrUp();
void isrDown();
void isrRight();
void isrLeft();
void isrEnter();
void isrButton(int pin, char *button);

// 現在押されているボタン名
static volatile char *currentButton = NULL;

// 押された時間
static volatile long currentButtonTime = 0; 

// メイン関数
int main(int argc, char *argv[]) {
	struct timeval now;

	// GPIOの初期化
	if (setupGpio() == -1) return 1;

	while (1) {
		sleep(1);

		// 現在、汎用ボタンが押されている場合
		// 他の汎用ボタンを最大RESET_SEC(5秒)間無効
		if (currentButton != NULL) {
			gettimeofday(&now, NULL);
			if (RESET_SEC < now.tv_sec - currentButtonTime) {
				currentButton = NULL;
			}
		}
	}
	return 0;
}

// GPIOの初期化関数
int setupGpio() {
	// WiringPiの初期化
	if (wiringPiSetupGpio() == -1) return -1;

	// 入力モードに設定 
	pinMode(GPIO_UP, INPUT);
	pinMode(GPIO_DOWN, INPUT);
	pinMode(GPIO_RIGHT, INPUT);
	pinMode(GPIO_LEFT, INPUT);
	pinMode(GPIO_ENTER, INPUT);

	// PULLUPモードに設定 
	pullUpDnControl(GPIO_UP, PUD_UP);
	pullUpDnControl(GPIO_DOWN, PUD_UP);
	pullUpDnControl(GPIO_RIGHT, PUD_UP);
	pullUpDnControl(GPIO_LEFT, PUD_UP);
	pullUpDnControl(GPIO_ENTER, PUD_UP);

	// GPIOの値の変化を検出し、割り込み処理を行う
	wiringPiISR(GPIO_UP, INT_EDGE_BOTH, &isrUp);
	wiringPiISR(GPIO_DOWN, INT_EDGE_BOTH, &isrDown);
	wiringPiISR(GPIO_RIGHT, INT_EDGE_BOTH, &isrRight);
	wiringPiISR(GPIO_LEFT, INT_EDGE_BOTH, &isrLeft);
	wiringPiISR(GPIO_ENTER, INT_EDGE_BOTH, &isrEnter);
	return 0;
}

// upボタンの割込み関数
void isrUp() {
	isrButton(GPIO_UP, "up");
}

// downボタンの割込み関数
void isrDown() {
	isrButton(GPIO_DOWN, "down");
}

// rightボタンの割込み関数
void isrRight() {
	isrButton(GPIO_RIGHT, "right");
}

// leftボタンの割込み関数
void isrLeft() {
	isrButton(GPIO_LEFT, "left");
}

// enterボタンの割込み関数
void isrEnter() {
	isrButton(GPIO_ENTER, "enter");
}

// ボタンの割込み関数
void isrButton(int pin, char *button) {
	int read1, read2;
	struct timeval now;

	// チャタリングによる誤動作防止のため
	// BUTTON_USLEEP(0.05秒)の間隔でGPIOの値を2回取得し
	// 一致する場合のみボタン名を表示
	read1 = digitalRead(pin);
	usleep(BUTTON_USLEEP);
	read2 = digitalRead(pin);
	if (read1 == 0 && read2 == 0) {
		if (currentButton == NULL) {
			gettimeofday(&now, NULL);
			currentButtonTime = now.tv_sec;
			currentButton = button;
			printf("%s\n", button);
		}
	} else if (currentButton == button && read1 == 1 && read2 == 1) {
		currentButton = NULL;
	}
}
