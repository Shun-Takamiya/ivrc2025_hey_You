// Arduinoの修正後コード

#define echoPin 2 // Echo Pin
#define trigPin 3 // Trigger Pin
// #define airFlowPin A0 // 風量センサーのアナログピン

double Duration = 0; 
double Distance = 0; 
float airFlow = 0; // 風量を格納する変数

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  // --- 距離センサーの計測 ---
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  Duration = pulseIn(echoPin, HIGH);
  if (Duration > 0) {
    Distance = (Duration / 2.0) * 340.0 * 100.0 / 1000000.0;
  } else {
    Distance = 0; // 測定失敗時は0にする
  }

  // --- 風量センサーの計測 ---
  //  int sensorValue = analogRead(airFlowPin);
  // ★★★↓この変換式は、お使いのセンサーの仕様に合わせて調整が必要です★★★
  // 例: 0-1023の値を0-100%に変換
  // airFlow = map(sensorValue, 0, 1023, 0, 100); 

  // --- データをカンマ区切りで送信 ---
  // Pythonで扱いやすいように、計算した距離の数値だけを送信する
  Serial.print(Distance);   // 1つ目のデータ（改行なし）
  Serial.print(",");        // 区切り文字のカンマ
  Serial.println(airFlow);  // 2つ目のデータ（最後に改行）

  delay(100); // 送信間隔を少し短くする
}