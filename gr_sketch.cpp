/*
* 圧電素子を使って簡易演奏するサンプル
* ntbt
* 参考：GR－SAKURAのTone利用サンプルを改良した
*/

#include <rxduino.h>

#define button0 30 //再生
#define button1 31 //停止
#define button2 32
#define button3 33
#define button4 35
#define spaeker 34 //圧電素子の接続先
 
int  buttons[5] = {button0 ,button1,button2,button3,button4};//スイッチの数
//音の種類
#define no 0 //音を鳴らさない場合
#define do0 440 //ド
#define dos0 466 //ド#
#define re0 494 //レ
#define res0 523 //レ#
#define mi0 554 //ミ
#define fa0 587 //ファ
#define fas0 622 //ファ#
#define so0 659 //ソ
#define sos0 699 //ソ#
#define ra0 740 //ラ
#define ras0 784 //ラ#
#define si0 830 //シ
#define do1 880 //ド
#define dos1 923 //ド#
#define re1 988 //レ
#define res1 1046 //レ#
#define mi1 1109 //ミ
#define fa1 1174 //ファ
#define fas1 1244 //ファ#
#define so1 1318 //ソ
#define sos1 1318 //ソ#
#define ra1 1480 //ラ
#define ras1 1568 //ラ#
#define si1 1661 //シ

//音符クラス?楽譜に刻まれる記号単位で記述
class onp{
public: //面倒なのでPublicとする
    int oto; //音の種類[周波数]：上記のDefineを利用
    int time; //音を継続してならす時間[ms]：下記のTime系のDefineを利用
    //
    onp(int o,int t)
    {//コンストラクタで中身を定義する
        this->oto = o;
        this->time = t;
    }
};

#define time_1 2000 //全音符
#define time_2 1000 //2分音符
#define time_4 500 //四分音符
#define time_8 250 //八分音符
#define time_16 125 //十六分音符
#define time_32 63 //三十二分音符
#define time_64 31 //六十四分音符?予備

#define MAX_G 57 //音符の最大数
onp gakuhu[MAX_G ] = //楽譜の内容配列
    {
    onp(no,time_4 ),onp(re0,time_4 ),onp(so0,time_4 ),onp(re1,time_4 ),onp(no,time_32 ),//re,so,res,do-
    onp(re1,time_2 ),onp(do1,time_2 ),onp(ras0,time_8 ),onp(ra0,time_8 ),onp(re0,time_8 ),//si,ra,re,fa,
    onp(fa0,time_8 ),onp(so0,time_2 ),onp(no,time_32 ),onp(so0,time_8 ),onp(si0,time_8 ),//so-,so,si,re,
    onp(re1,time_8 ),onp(fa1,time_2 ),onp(no,time_16 ),onp(fa1,time_8 ),onp(do1,time_8 ),
    onp(no,time_4 ),onp(re1,time_8 ),onp(fa1,time_8 ),onp(do1,time_8 ),onp(no,time_4 ),
    onp(re1,time_8 ),onp(fa1,time_8 ),onp(no,time_32 ),onp(ras0,time_8 ),onp(ra0,time_8 )//si,ra,re,fa,
    ,onp(re0,time_8 ),onp(fa0,time_8 ),onp(so0,time_2 ),onp(no,time_4 ),onp(no,time_4 )//半分@35
    ,
    onp(no,time_4 ),onp(re0,time_4 ),onp(so0,time_4 ),onp(re1,time_4 ),onp(no,time_32 ),//re,so,res,do-
    onp(re1,time_2 ),onp(do1,time_2 ),onp(ras0,time_8 ),onp(ra0,time_8 ),onp(re0,time_8 ),//si,ra,re,fa,
    onp(fa0,time_8 ),onp(so0,time_2 ),onp(no,time_32 ),onp(so0,time_8 ),onp(si0,time_8 ),//so-,so,si,re,
    onp(re1,time_8 ),onp(fa1,time_2 ),onp(re1,time_4 ),onp(mi1,time_2 ),onp(do1,time_4 ),
    onp(re1,time_2 ),onp(no,time_2 )//半分
    };


int play = 0; //実行モード変数＠再生＠デフォルト＝停止
int time_id = 0; //楽譜の再生ID＠時間

void debug(int c) //debug関数＠GR－SAKURAのLED4つを利用
{
	digitalWrite(PIN_LED0, c &1);
	digitalWrite(PIN_LED1, c &2);
	digitalWrite(PIN_LED2, c &4);
	digitalWrite(PIN_LED3, c &8);
};
 
// setup() は最初に一回だけ実行されるところです
// ピンの初期化などに使います
 
void setup()
{
	// PULLUP とすることで常に入力がHIGH（電気が流れている状態）になります
	for(int i=0;i<5;i++)
	{
		pinMode( buttons[i], INPUT_PULLUP );
	}
	//デフォルトLEDの出力設定
    pinMode(PIN_LED0,OUTPUT);
    pinMode(PIN_LED1,OUTPUT);
    pinMode(PIN_LED2,OUTPUT);
    pinMode(PIN_LED3,OUTPUT);
 
	// スピーカーは出力になりますので OUTPUT とします
	pinMode( spaeker, OUTPUT);
}


// loop() は繰り返し実行されるところです
// ここにプログラムの本体を記述します
 
void loop()
{
	if( digitalRead( buttons[0]) == LOW )
	{//再生
		play = 1;
	}
	if( digitalRead( buttons[1]) == LOW )
	{//停止
		play = 0;
		noTone(spaeker);//スピーカを鳴らさない為
	}
	//演奏
	if(play == 1)
	{//再生時
		if(gakuhu[time_id].oto == no)
		{//休符
			noTone(spaeker);
		}
		else
		{//通常
			tone(spaeker, gakuhu[time_id].oto );
		}
		debug(time_id);//debugモード
		delay(gakuhu[time_id].time );//指定時間分だけDelayを掛ける
		//
		time_id ++;//楽譜を進める
		if(time_id >= MAX_G)
			time_id =0;//最大ならば初期に戻す
	}
     // このまま loop() の最初に戻りますが、delay(10)とすることで10ミリ秒処理を止めています。
     // 一見不要に見えますが、これが無いと音がきれいに鳴りません。
     delay(10) ;
}
