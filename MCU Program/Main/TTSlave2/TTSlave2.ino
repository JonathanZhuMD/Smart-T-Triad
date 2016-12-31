

#define ST 36
#define D1 34
#define D2 32
#define D3 30
#define D4 28
#define INH1 26
#define INH2 24

#define IR_TRANS_SUM 52
#define FIRST_IR_TRANS_BOARD 2

#define DELAY_AFTER_STROBE 200    //In macro second
#define DELAY_DEBUGGING_ROUND 00    //In Mili second

bool malFunctionIRTrans[12][28];

void setup() 
{
	Serial.begin(9600);
	Serial1.begin(9600);

	while(!Serial.available());

	manInit();
	malFunctionIRTransDetect();
}




void manInit()
{
	pinMode(D1,OUTPUT);
	pinMode(D2,OUTPUT);
	pinMode(D3,OUTPUT);
	pinMode(D4,OUTPUT);
	pinMode(INH1,OUTPUT);
	pinMode(INH2,OUTPUT);

	digitalWrite(D1,LOW);
	digitalWrite(D2,LOW);
	digitalWrite(D3,LOW);
	digitalWrite(D4,LOW);
	digitalWrite(INH1,LOW);
	digitalWrite(INH2,HIGH);

	pinMode(IR_TRANS_SUM,INPUT);

	for(int i=FIRST_IR_TRANS_BOARD;i<FIRST_IR_TRANS_BOARD+12;i++)
	{
		pinMode(i,INPUT);
	}

	for(int i=0;i<12;i++)
	{
		for(int x=0;x<28;x++)
		{
			malFunctionIRTrans[i][x]=false;
		}
	}
}




void loop()
{
	scanSensorArray();
}




void scanSensorArray()
{
	digitalWrite(INH2,HIGH);
	digitalWrite(INH1,LOW);
	signalSwitch(0);

	for(int i=1;i<=13;i++)
	{
		signalSwitch(i);
	}

	digitalWrite(INH1,HIGH);
	digitalWrite(INH2,LOW);
	signalSwitch(14);

	for(int i=15;i<=27;i++)
	{
		signalSwitch(i);
	}
}




void signalSwitch(int number)
{
	int number1=number;
	if(number>=14)
		number-=14;

	digitalWrite(D1,bitRead(number,0));
	digitalWrite(D2,bitRead(number,1));
	digitalWrite(D3,bitRead(number,2));
	digitalWrite(D4,bitRead(number,3));

	STFlash();
	delayMicroseconds(DELAY_AFTER_STROBE);

	scanIRTrans(number1);

	delay(DELAY_DEBUGGING_ROUND);
}




void STFlash()
{
	digitalWrite(ST,HIGH);
	digitalWrite(ST,LOW);
}
