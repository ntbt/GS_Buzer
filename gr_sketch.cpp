#include <rxduino.h>
 
 
// 基板上のピンの番号に名前をつけます
// 以後、プログラム上では button1 と書けば、0番のピンを指していることになります
 
#define button0 30
#define button1 31
#define button2 32
#define button3 33
#define button4 35
#define spaeker 34
 
int  buttons[5] = {button0 ,button1,button2,button3,button4};
#define no 0
#define do0 440
#define dos0 466
#define re0 494
#define res0 523
#define mi0 554
#define fa0 587
#define fas0 622
#define so0 659
#define sos0 699
#define ra0 740
#define ras0 784
#define si0 830
#define do1 880
#define dos1 923
#define re1 988
#define res1 1046
#define mi1 1109
#define fa1 1174
#define fas1 1244
#define so1 1318
#define sos1 1318
#define ra1 1480
#define ras1 1568
#define si1 1661

class onp{
public:
    int oto;
    int time;
    //
    onp(int o,int t)
    {
        this->oto = o;
        this->time = t;
    }
};

#define time_1 2000
#define time_2 1000
#define time_4 500
#define time_8 250
#define time_16 125
#define time_32 63
#define time_64 31

#define MAX_G 57
onp gakuhu[MAX_G ] = 
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


int play = 0;
 int time_id = 0;
 
 void debug(int c)
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
 
     // ボタンが押されたことを感知するためにピンを入力モードにします
     // PULLUP とすることで常に入力がHIGH（電気が流れている状態）になります
 
     for(int i=0;i<5;i++)
     {
         pinMode( buttons[i], INPUT_PULLUP );
    }
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
 
     // ボタンが押されるとGNDに繋がります
     // そのため、ピンに流れていた電気がGNDに流れるのでピンはLOW（電気が流れていない状態）になります。
     // ここではそれぞれのピンの状態を調べて、LOWだったらtone()を使ってスピーカーから音を出す処理をしています。
 if( digitalRead( buttons[0]) == LOW )
     play = 1;
if( digitalRead( buttons[4]) == LOW )
 {
     play = 0;
     noTone(spaeker);
}
     
 if(play == 1)
 {
      if(gakuhu[time_id].oto == no)
          noTone(spaeker);
      else
          tone(spaeker, gakuhu[time_id].oto );
      debug(time_id);
      delay(gakuhu[time_id].time );
      //
      time_id ++;
      if(time_id >= MAX_G)
          time_id =0;
}
     /*if( digitalRead( buttons[0]) == LOW &&  digitalRead( buttons[1]) == LOW ) {
          tone( spaeker, 262 ) ;  // ド
          tone( spaeker, 294 ) ;  // レ
     } else if( digitalRead( buttons[0]) == LOW &&  digitalRead( buttons[3]) == LOW ) {
          tone( spaeker, 277 ) ;  // %ド
     } else if( digitalRead( buttons[0]) == LOW ) {
          tone( spaeker, 262 ) ;  // ド
     } else if( digitalRead( buttons[1]) == LOW ) {
          tone( spaeker, 294 ) ;  // レ
     } else if( digitalRead( buttons[2]) == LOW ) {
          tone( spaeker, 330 ) ;  // ミ
     } else if( digitalRead( buttons[3]) == LOW ) {
          tone( spaeker, 349 ) ;  // ファ
     } else if( digitalRead( buttons[4]) == LOW ) {
          tone( spaeker, 392 ) ;  // ソ
     } else {
          noTone( spaeker ) ;
     }*/
 /*
 ド：２６１．６３Hz
レ：２９３．６６Hz
ミ：３２９．６３Hz
ファ：３４９．２３Hz
ソ：３９２．００Hz
ラ：４４０．００Hz
シ：４９３．８８Hz（小数点第３位四捨五入）
 */
     // このまま loop() の最初に戻りますが、delay(10)とすることで10ミリ秒処理を止めています。
     // 一見不要に見えますが、これが無いと音がきれいに鳴りません。
 
     delay(10) ;
}