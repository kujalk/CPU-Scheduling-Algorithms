/* sketch 3 
turn on a LED when the button is pressed and let it on 
until the button is pressed again
*/


//LEDs
int RED = 13;
int GREEN = 12;
int BLUE = 11;
int ORANGE = 10;

int stateLED = LOW;
int stateButton1;
int stateButton2;
int stateButton3;
int stateButton4;
int postselect1;
int postselect2;

int pinButton1 = 3;
int pinButton2 = 4;
int pinButton3 = 5;
int pinButton4 = 6;
int pinButton5 = 2;
int select1=9;
int select2=8;




int previous1=LOW;
int previous2=LOW;
int previous3=LOW;
int previous4=LOW;
int preselect1=LOW;
int preselect2=LOW;


//array 
int array[4];
int queue[4];
int time[4];

// put and call
int put=0;
int call=0;
int count=0;
int tr=0;
int previous;

int minimum;




 
void setup() {
  pinMode(pinButton1, INPUT);
  pinMode(pinButton2, INPUT);
  pinMode(pinButton3, INPUT);
  pinMode(pinButton4, INPUT);
  pinMode(pinButton5, INPUT);
  pinMode(select1, INPUT);
  pinMode(select2, INPUT);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(ORANGE, OUTPUT);
  
  //initializing array
queue[0]=0;
queue[1]=0;
queue[2]=0;
queue[3]=0;

time[0]=0;
time[1]=0;
time[2]=0;
time[3]=0;

attachInterrupt(0,check,CHANGE);

}
 
 //******************Loop****************************
void loop() {
//execute_SJFPreem();
//execute_RR();
//execute_SJF();
//execute_FCFS();

  postselect1 = digitalRead(select1);
  postselect2 = digitalRead(select2);
  
  if(postselect1==LOW && postselect2==LOW)
  {
	  execute_FCFS();
  }
  else if (postselect1==LOW && postselect2==HIGH)
  {
	 execute_SJF(); 
  }
  else if (postselect1==HIGH && postselect2==LOW)
  {
	 execute_SJFPreem(); 
  }
  else if (postselect1==HIGH && postselect2==HIGH)
  {
	 execute_RR();
  }
  
 
}
//****************************************************

//check function********************************

void check()
{
  stateButton1 = digitalRead(pinButton1);
  stateButton2 = digitalRead(pinButton2);
  stateButton3 = digitalRead(pinButton3);
  stateButton4 = digitalRead(pinButton4);
  
  //2nd time
  if(count==0)
    put=0;
  
  //red
  if(previous1==LOW && stateButton1==HIGH)
  {
	  array[put]=13;
	  queue[put]=5;
	  time[put]=trick();
	  put=put+1;
	  count=count+1;
  }
  previous1=stateButton1;
  
   //green
  if(previous2==LOW && stateButton2==HIGH)
  {
	  array[put]=12;
	  queue[put]=10;
	  time[put]=trick();
	  put=put+1;
	  count=count+1;
  }
  previous2=stateButton2;
  
   //red
  if(previous3==LOW && stateButton3==HIGH)
  {
	  array[put]=11;
	  queue[put]=15;
	  time[put]=trick();
	  put=put+1;
	  count=count+1;
  }
  previous3=stateButton3;
  
   //red
  if(previous4==LOW && stateButton4==HIGH)
  {
	  array[put]=10;
	  queue[put]=20;
	  time[put]=trick();
	  put=put+1;
	  count=count+1;
  }
  previous4=stateButton4;
}

//blink led ********************************

void blink_led()
{
	 digitalWrite(array[call], HIGH);
    delay(1000);
    digitalWrite(array[call], LOW);
    delay(500);
}

//Round Robin***********************************

void execute_RR()
{
	//check();
	
		if(count==0)
		{
			delay(1);
			call=0;
		}
	
		else
		{
			for(int v=0;v<4;v++)
			{
				if((time[v]!=0))
				{
					minimum=time[v];
					call=v;
					break;
				}
			}
		
		
		//finiding minimum
	
	for(int z=0;z<4;z++)
	{
		if((time[z]<minimum) && (time[z]!=0))
		{
			call=z;
			minimum=time[z];
		}
	}
	
	
		if(queue[call]>=3)
		{
			for(int a=0;a<3;a++)
			{
				blink_led();
			}
			queue[call]=queue[call]-3;
			time[call]=trick();
		}
		
		else //final remaining time is less than 3
		{
			for(int b=queue[call];b>0;b--)
			{
				blink_led();
			}
			queue[call]=0;
			count=count-1;
			time[call]=0;
		}
	
}
 
}

//trick

int trick()
{
	tr=tr+1;
	return tr;
}


//SJF non- preemtive*******************************
void execute_SJF()
{
	//check();
	
		if(count==0)
		{
			delay(1);
			call==0;
		}
	
		else
		{
			for(int v=0;v<4;v++)
			{
				if((queue[v]!=0))
				{
					minimum=queue[v];
					call=v;
					break;
				}
			}
		
		
		//finiding minimum
	
	for(int z=0;z<4;z++)
	{
		if((queue[z]<minimum) && (queue[z]!=0))
		{
			call=z;
			minimum=queue[z];
		}
	}
	
	
		
			for(int a=queue[call];a>0;a--)//execute the short job first
			{
				blink_led();
			}
			queue[call]=0;//after execution mark it as zero
			count=count-1;
		
	
		} 
 
}

//SJF Preemtive*****************************************************

void execute_SJFPreem()
{
	previous=count;
	
		if(count==0)
		{
			delay(1);
			call=0;
		}
	
		else
		{
			for(int v=0;v<4;v++)
			{
				if((queue[v]!=0))
				{
					minimum=queue[v];
					call=v;
					break;
				}
			}
		
		//finiding minimum
	
	for(int z=0;z<4;z++)
	{
		if((queue[z]<minimum) && (queue[z]!=0))
		{
			call=z;
			minimum=queue[z];
		}
	}
			
			while(queue[call]>0)
			{
				if(count!=previous)
				{
					break;
				}
				blink_led();
				queue[call]=queue[call]-1;
			}
			
		//	queue[call]=0;//after execution mark it as zero
		
		if(queue[call]==0)
		{
			count=count-1;
		}
			
		}

}

//First come First Serve*********************************************
void execute_FCFS()
{
	//check();
	
	if((queue[call]<=0) && (call!=0))
	{
		if(count>=1)
			call=call+1;
		else
			call=0;
	}
	
	else if ((queue[call]<=0) && (call==0))
	{
		
			delay(1);
	}
	
	else
	{
		
			for(int b=queue[call];b>0;b--)
			{
				blink_led();
			}
			queue[call]=0;
			count=count-1;
			call=call+1;
		
	}
	
	
	if(call==4)//if call go beyond array limit
	{
		call=0;
	}
}