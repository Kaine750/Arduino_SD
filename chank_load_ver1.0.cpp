#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#define rep(i,n) for(int i = 0;i <(int)n;i++)

File dataFile;

const int CS = 4;

void setup() {
    Serial.begin(9600); //シリアル通信開始
    Serial.println("Initializing SD.....");
    pinMode(10, OUTPUT);

    if (!SD.begin(CS)) {
        Serial.println("not found SD");
    } 
    else {
        Serial.println("SD OK");
        dataFile = SD.open("log.txt", FILE_WRITE);
        
        if (dataFile) {
         Serial.print("Writing to log.txt..."); //シリアルコンソールに値を表示
         dataFile.println("tetsing 1, 2, 3."); //SDに文字列を書き込み
         dataFile.close();
         Serial.println("done");
        } 
        else {
          Serial.println("File write error!");
    }
    }
    dataFile = SD.open("log.txt");
    if (dataFile) {
      Serial.println("log.txt:");

    // read from the file until there's nothing else in it:
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    // close the file:
    dataFile.close();
    } 
    else {
    // if the file didn't open, print an error:
    Serial.println("error opening log.txt");    
    }
}


void loop_map(char field_map[200][100], short int length, short int width) {
    File dataFile = SD.open("log.txt", FILE_WRITE);
    char datachar[length][width] = {}; //char型の宣言
    rep(i,length){
        rep(j,width){
            datachar[i][j] = field_map[i][j];
        }
    }
        
    if (dataFile) {
        Serial.println("datachar"); //シリアルコンソールに値を表示
        dataFile.println("datachar"); //SDに文字列を書き込み
        dataFile.close();
    } else {
        Serial.println("File write error!");
    }
    delay(60000);
}

void importing(char chunk_imp[4][11][11], short int cur_x, short int cur_y, short int rel_x, short int rel_y){
    File dataFile = SD.open("log.txt", FILE_WRITE);
    if(dataFile){
        while(dataFile.available()){
            Serial.write(dataFile.read());
        }
        rep(i, 11){
            rep(j, 11){
                dataFile[i + cur_x + rel_x][j + cur_y + rel_y].println(chunk_imp[0][i][j]);
                }
                }
        for(short int i = 0;i > -11;i--){
            rep(j, 11){
                dataFile[j + cur_x - rel_x][k + cur_y + rel_y].println(chunk_imp[1][j][k]);
                }
                }
        for(short int i = 0;i > -11;i--){
            for(short int j = 0;j > -11;j--){        
                dataFile[j + cur_x - rel_x][k + cur_y - rel_y].println(chunk_imp[2][j][k]);
                }
                }
        rep(i, 11){
            for(short int j = 0;j > -11;j--){        
                dataFile[j + cur_x + rel_x][k + cur_y - rel_y].println(chunk_imp[3][j][k]);
                }
                }
    }
}
        dataFile.close();
}
delay(2000);
}

void exporting(char chunk_map[4][11][11], short int cur_x, short int cur_y, short int rel_x, short int rel_y){
    const short int x_limit = 100;
    const short int y_limit = 50;
    File dataFile = SD.open("log.txt");
    if(dataFile){
        while(dataFile.available()){
            Serial.write(dataFile.read());
        }
        //vector<vector<int> > chank_map(chank_num,vector<int>(chank_num,0));
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
void r_theta_table(unsigned char r_theta_map, short int rel_x_1, short int rel_y_1){
    const float conv = 53.715; //(180 * 90 / M_PI / 96)
    rep(i, 15){
        rep(j, 15){
                r_theta_map[0][i][j] = (i + rel_x_1)(i + rel_x_1) + (j + rel_y_1)(j + rel_y_1);
                float radian = atan((j + rel_y_1)/(i + rel_x_1));
                r_theta_map[1][i][j] = radian * conv;
        }
    }
}

//PLANB
void chank_11(char chunk_map, short int cur_x, short int cur_y, short int rel_x, short int rel_y){
    const short int x_limit = 100;
    const short int y_limit = 50;
    File dataFile = SD.open("log.txt");
    if(dataFile){
        while(dataFile.available()){
            Serial.write(dataFile.read());
        }
        //vector<vector<int> > chank_map(chank_num,vector<int>(chank_num,0));
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

void SD_read_map(char map_memory, short int X, short int Y){ //X,Yは12 map_memoryは12*5*5
    File dataFile = SD.open("log.txt");
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

void loop() {
  // put your main code here, to run repeatedly:

}