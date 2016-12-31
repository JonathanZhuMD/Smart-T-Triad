#define SER_1 9600
#define SER_2 115200


void scanIRTrans(int number)
{
	if(digitalRead(IR_TRANS_SUM)==HIGH)
	{
		for(int z=0; z<12; z++)
		{
		    if(!malFunctionIRTrans[z][number] && digitalRead(FIRST_IR_TRANS_BOARD+z)==HIGH)
		    {
		    	serprintln("Triggered at board: "+String(z)+"    Position: "+String(number));
		    	Serial1.println(String(z)+","+String(number));
          serprintln(String(z)+","+String(number));
		    	return;
		    	delay(DELAY_DEBUGGING_ROUND);
		    }
		}
		//serprintln("Triggered at position: "+String(number)+"   But position Unknow!");
	}
}


void serprint(String message)
{
	Serial.print(message);
} 

void serprintln(String message)
{
	Serial.print("\n");
	Serial.print(message);
}
