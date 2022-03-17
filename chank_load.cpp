#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#define rep(i,n) for(int i = 0;i <(int)n;i++)


const int CS = 4;

void setup() {
    Serial.begin(9600); //シリアル通信開始
    Serial.println("Initializing SD.....");//"Initializing SD....."と表示
    pinMode(10, OUTPUT);

    if (!SD.begin(CS)) {
        Serial.println("not found SD");//SDカードが軌道できなかったら表示
    } else {
        Serial.println("SD OK");
    }
}

void loop(char length, char width) {
    char datachar[length][width] = []; //char型の宣言
    rep(i,length){
        rep(j,width){
            datachar[i][j] = field_map[i][j];
        }
    }
    File dataFile = SD.open("log.txt", FILE_WRITE); //"log.txt"にマップを入れる
    
    if (dataFile) {
        Serial.println(datachar); //シリアルコンソールに値を表示
        dataFile.println(datachar); //SDに文字列を書き込み
        dataFile.close();
    } else {
        Serial.println("File write error!");
    }
    delay(60000);
}

void importing(char chunk_imp[4][11][11], short int cur_x, short int cur_y, short int rel_x, short int rel_y){ //SDカードに[4][11][11]のチャンクを読み込み
    File dataFile = SD.open("log.txt");                                                                        //(cur_x,cur_y)は現在地,(rel_x,rel_y)は相対座標
    if(dataFile){
        while(dataFile.available()){
            Serial.write(dataFile.read());
        }
        rep(i, 11){                                                                                            //点・線対象に読み込み
            rep(j, 11){
                dataFile[i + cur_x + rel_x][j + cur_y + rel_y].println(chunk_imp[0][i][j]);}}
        for(short int i = 0;i > -11;i--){
            rep(j, 11){
                dataFile[j + cur_x - rel_x][k + cur_y + rel_y].println(chunk_imp[1][j][k]);}}
        for(short int i = 0;i > -11;i--){
            for(short int j = 0;j > -11;j--){        
                dataFile[j + cur_x - rel_x][k + cur_y - rel_y].println(chunk_imp[2][j][k]);}}
        rep(i, 11){
            for(short int j = 0;j > -11;j--){        
                dataFile[j + cur_x + rel_x][k + cur_y - rel_y].println(chunk_imp[3][j][k]);}}
    }
}
        dataFile.close();
}
delay(2000);
}

void chunk_upload(char chunk_map[4][11][11], short int cur_x, short int cur_y, short int rel_x, short int rel_y){ //[4][11][11]のチャンクにSDカードから書き込み
    const short int x_limit = 100;                                                                                //(cur_x,cur_y)は現在地,(rel_x,rel_y)は相対座標
    const short int y_limit = 50;                                                                                 //limit_x,limit_yを超えると0(未探索)を返す
    File dataFile = SD.open("log.txt");
    if(dataFile){
        while(dataFile.available()){
            Serial.write(dataFile.read());
        }
        //vector<vector<int> > chank_map(chunk_num,vector<int>(chunk_num,0));
        if(abs(11 + j + cur_x + rel_x) <= 100 && abs(11 + j + cur_y + rel_y) <= 50){  
            rep(i, 11){
                rep(j, 11){
                    chunk_map[0][j][k] = dataFile[j + cur_x + rel_x][k + cur_y + rel_y];}}
            for(short int i = 0;i > -11;i--){
                rep(j, 11){
                    chunk_map[1][j][k] = dataFile[j + cur_x - rel_x][k + cur_y + rel_y];}}
            for(short int i = 0;i > -11;i--){
                for(short int j = 0;j > -11;j--){
                    chunk_map[2][j][k] = dataFile[j + cur_x - rel_x][k + cur_y - rel_y];}}
            rep(i, 11){
                for(short int j = 0;j > -11;j--){         
                    chunk_map[3][j][k] = dataFile[j + cur_x + rel_x][k + cur_y - rel_y];}}
        }
        else{
                chunk_map[0][j][k] = 0;
                chunk_map[1][j][k] = 0;
                chunk_map[2][j][k] = 0;
                chunk_map[3][j][k] = 0;
        }
        }
        }
        }
        dataFile.close();
    }
    delay(2000);
}

#include <math.h>
void r_theta_table(unsigned char r_theta_map[2][15][15], short int rel_x_1, short int rel_y_1){ //rとthetaの表.与えられた相対座標のものを計算
    const float conv = 40.286; //(180 * 90 / M_PI / 128)
    rep(i, short int 15){
        rep(j, short int 15){
                r_theta_map[0][i][j] = (i + rel_x_1)(i + rel_x_1) + (j + rel_y_1)(j + rel_y_1);
                float radian = atan((j + rel_y_1)/(i + rel_x_1));
                r_theta_map[1][i][j] = radian * conv;
        }
    }
}

//PLANB
void chunk_11(char chunk_map[22][22], short int cur_x, short int cur_y, short int rel_x, short int rel_y){ //[22][22]のチャンクをSDカードから書き込み
    const short int x_limit = 100;
    const short int y_limit = 50;
    File dataFile = SD.open("log.txt");
    if(dataFile){
        while(dataFile.available()){
            Serial.write(dataFile.read());
        }
        //vector<vector<int> > chunk_map(chunk_num,vector<int>(chunk_num,0));
        if(abs(22 + j + cur_x + rel_x) <= 100 && abs(22 + j + cur_y + rel_y) <= 50){  
            rep(i, 22){
                rep(j, 22){
                    chunk_map[j][k] = dataFile[j + cur_x + rel_x][k + cur_y + rel_y];}}
            //for(short int i = 0;i > -11;i--){
            //    rep(j, 11){
            //        chunk_map[1][j][k] = dataFile[j + cur_x - rel_x][k + cur_y + rel_y];}}
            //for(short int i = 0;i > -11;i--){
            //    for(short int j = 0;j > -11;j--){
            //        chunk_map[2][j][k] = dataFile[j + cur_x - rel_x][k + cur_y - rel_y];}}
            //rep(i, 11){
            //    for(short int j = 0;j > -11;j--){         
            //        chunk_map[3][j][k] = dataFile[j + cur_x + rel_x][k + cur_y - rel_y];}}
        }
        else{
                chunk_map[j][k] = 0;
                //chunk_map[1][j][k] = 0;
                //chunk_map[2][j][k] = 0;
                //chunk_map[3][j][k] = 0;
        }
        }
        }
        }
        dataFile.close();
    }
    delay(2000);
}

void SD_read_map(char map_memory[12][5][5], short int X[12], short int Y[12]){ //X,Yは[12],map_memoryは[12][5][5]
    File dataFile = SD.open("log.txt");                                        //SDカードから読み込み
    if(dataFile){
        while(dataFile.available()){
            Serial.write(dataFile.read());
        }
    rep(a, 12)
        rep(i, 5){
            rep(j, 5){
                map_memory[a][i][j] = dataFile[X[a] + i][Y[a] + j];
        }
    }
    dataFile.close();
    }
    delay(2000);
}
