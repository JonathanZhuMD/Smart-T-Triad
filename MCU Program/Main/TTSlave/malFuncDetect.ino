


void malFunctionIRTransDetect()
{
	digitalWrite(INH2,HIGH);
	digitalWrite(INH1,LOW);
	malSignalSwitch(0);

	for(int i=1;i<=13;i++)
	{
		malSignalSwitch(i);
	}

	digitalWrite(INH1,HIGH);
	digitalWrite(INH2,LOW);
	malSignalSwitch(14);

	for(int i=15;i<=27;i++)
	{
		malSignalSwitch(i);
	}

	serprintln("*** Below are the malfunction IR Trans Map: ***");
	serprintln("");

	for(int i=0; i<12; i++)
	{
		serprintln("");
		for(int x=0; x<28; x++)
		{
			serprint(String(malFunctionIRTrans[i][x])+"  ");       
		}   
	}
}



void malSignalSwitch(int number)
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

	serprintln("Testing Sensor at position: "+String(number1));

	if(digitalRead(IR_TRANS_SUM)==HIGH)
	{
		serprintln("Triggered! Running futher testing......");
	    for(int x=0; x<12; x++)
	    {
	    	if(digitalRead(FIRST_IR_TRANS_BOARD+x)==HIGH)
	    	{
	    		malFunctionIRTrans[x][number1]=true;

	    		serprintln("Malfunction Sensor Detected! At board: "+String(x)+"    Position: "+String(number1));
	    	}    
	    }
	}

	delay(DELAY_DEBUGGING_ROUND);
}

