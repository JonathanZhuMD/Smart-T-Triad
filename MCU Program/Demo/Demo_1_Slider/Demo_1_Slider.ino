// Demo_1_Slider.ino

int OPin[5]={5,6,9,10,3

};


void setup() 
{
	for(int i=0; i<5; i++)
	{
	    pinMode(OPin[i], OUTPUT);
	    analogWrite(OPin[i], 0);
	}


	Serial.begin(9600);
	while(!Serial.available());
}

void loop() 
{
	while(!Serial.available());

	delay(100);

	String tempstr=Serial.readString();

	int place=tempstr.substring(0,1).toInt();

	int val=tempstr.substring(2).toInt();

	analogWrite(OPin[place], val*9);

	Serial.println("Port: "+String(OPin[place])+"   was set to val: "+String(val*9));
}

