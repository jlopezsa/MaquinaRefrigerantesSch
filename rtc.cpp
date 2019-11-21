//====================================================================
// File Name : rtc.c
// Function  : S3C2450 RTC Test Program
// Date      : June. 5, 2006
// Version   : 0.0
// History
//   0.0 : Programming start (June. 05, 2006)
//====================================================================

#include "System.h"
#include "rtc.h"


//added
#include "auto_typedefine.h"
#include "autotest_api.h"
//added-end


char *day[8] = {" ","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
volatile U32 Tick=0, Alarm=0, transtime = 0;

void RTC_tick_CLKRST(void);
void __irq Rtc_Tick_ISR_clkrst(void);

void * rtc_func[][2]=
{
	(void *)RTC_time_tick,		"RTC Time Tick Int Test		",
	(void *)RTC_initialize,			"RTC time initialize        ",	
	(void *)Rtc_Alarm,			"RTC Alarm Test	",
	//(void *)RTC_BATFLT,			"RTC battery falut check Test	",
//	(void *)RTC_Display,			"RTC Display		",
//	(void*)RTC_SetTime,			"RTC Set Time	",
//	(void*)RTC_tick_CLKRST, 		"RTC Clock reset test	",
	0,0
};


void Test_RTC(void)
{
	
	
	while(1) {
		int i=0;
		printf("\n");
		while(1)
		{   //display menu
	    	printf("%2d:%s",i,rtc_func[i][1]);
	    	i++;
	    	if((int)(rtc_func[i][0])==0)
	    	{
				printf("\n");
				break;
	    	}
	    	if((i%4)==0) printf("\n");
		}
		printf("\nSelect(-1 to exit): ");
		i = GetIntNum();

		if(i==-1) break;

		if(i>=0 && (i<(sizeof(rtc_func)/4)) ) 
	    	( (void (*)(void)) (rtc_func[i][0]) )();	// execute selected function.
	}
}


void RTC_initialize(void)
{
	int year,month,date,hour,min,sec;

	year =  6;
	month= 12;
	date = 31;
	hour = 23;
	min  = 59;
	sec  = 00;
	
    	rRTCCON  = rRTCCON  | 0x1;		//RTC Control enable

    	rBCDYEAR =( ((year/10)<<4) + (year%10) );
    	rBCDMON  =( ((month/10)<<4)+ (month%10));
    	rBCDDATE =( ((date/10)<<4) + (date%10) );     	
    	rBCDDAY  = rBCDDAY  & ~(0x7)  | 0x3;		//SUN:1 MON:2 TUE:3 WED:4 THU:5 FRI:6 SAT:7
    	rBCDHOUR =( ((hour/10)<<4) + (hour%10) );
    	rBCDMIN  =( ((min/10)<<4)  + (min%10)  );
    	rBCDSEC  =( ((sec/10)<<4)  + (sec%10)  );     	

    	//rRTCCON  = rRTCCON  & ~(0x1);	//RTC Control disable

  	while (!Uart_GetKey()){	
    		printf("%2x : %2x : %2x  %10s,  %2x/%2x/20%02x\n",rBCDHOUR,rBCDMIN,rBCDSEC,day[rBCDDAY],rBCDMON,rBCDDATE,rBCDYEAR);
  	}
}

void RTC_Display(void)
{
	int i;
	while (!Uart_GetKey())
	{	
		if ( !(i == rBCDSEC))
		{
			printf("%2x : %2x : %2x  %10s,  %2x/%2x/20%02x\n",rBCDHOUR,rBCDMIN,rBCDSEC,day[rBCDDAY],rBCDMON,rBCDDATE,rBCDYEAR);	
			i = rBCDSEC;
		}
	}
	

}



void RTC_time_tick(void)
{
	int i;
	transtime = 0;
	
	
	RTC_Init();

	printf("[0]1/16384\t[1]:1/8192\t[2]1/4096\t[3]1/2048\t[4]1/128\t[5]1/1\n[6]1/1024\n"
		"[7]1/512\t[8]1/256\t[9]1/64\t\t[10]1/32\t[11]1/16\n[12]1/8\t\t[13]1/4\t\t[14]1/2\t\t[15]1/32768\t :\n");

	i=GetIntNum();
	if (i<0 && i>15 ) return ;
	if (i==15)
		rRTCCON = (rRTCCON & ~(0x1<<4)) | (1<<4);
	else	
		rRTCCON = (rRTCCON & ~(0xf<<5)&~(0x1<<4) ) | (i<<5)|(0<<4);
	
	printf(" rtcon = %08x\n", rRTCCON);



	#if 0 //yym for tick clock check changing Tick SEL
		
		rTICNT2 = 0;
		rTICNT0 = 0;
		rTICNT1 = 100;
		

	#endif
	
	#if 1
	switch(i)
		{
			// tick interval = 1/tick_clock * (tick_count +1)
			#if 1
			case 0: 	Tick_Count_Set(16384); break;
			case 1: 	Tick_Count_Set(8192); break;
			case 2: 	Tick_Count_Set(4096); break;
			case 3: 	Tick_Count_Set(2048); break;
			case 4: 	Tick_Count_Set(128); break;
			case 5: 	Tick_Count_Set(1); break;			
			case 6: 	Tick_Count_Set(1024); break;			
			case 7: 	Tick_Count_Set(512); break;	
			case 8: 	Tick_Count_Set(256); break;	
			case 9: 	Tick_Count_Set(64); break;	
			case 10: 	Tick_Count_Set(32); break;	
			case 11: 	Tick_Count_Set(16); break;	
			case 12: 	Tick_Count_Set(8); break;	
			case 13: 	Tick_Count_Set(4); break;
			case 14: 	Tick_Count_Set(2); break;	
			case 15: 	Tick_Count_Set(32768); break;	

			default : break;
			
			#elif 0  // for tick interval test
			case 0: 	Tick_Count_Set(1); break;
			case 1: 	Tick_Count_Set(1); break;
			case 2: 	Tick_Count_Set(1); break;
			case 3: 	Tick_Count_Set(1); break;
			case 4: 	Tick_Count_Set(1); break;
			case 5: 	Tick_Count_Set(1); break;			
			case 6: 	
					rRTCCON &= ~(7<<5);
					rRTCCON |= (1<<4); 
					printf(" rtcon = %08x\n", rRTCCON);
					Tick_Count_Set(1); 
					break;			
			default : break;
			
			#elif 0 // for tick clock resolution
			case 0: 	Tick_Count_Set(2); break;
			case 1: 	Tick_Count_Set(2); break;
			case 2: 	Tick_Count_Set(2); break;
			case 3: 	Tick_Count_Set(2); break;
			case 4: 	Tick_Count_Set(2); break;
			case 5: 	Tick_Count_Set(2); break;			
			case 6: 	
					rRTCCON &= ~(7<<5);
					rRTCCON |= (1<<4); 
					printf(" rtcon = %08x\n", rRTCCON);
					Tick_Count_Set(2); 
					break;			
			default : break;
			
				
			
			#endif
			
	
		}
	#endif

	
  	pISR_TICK = (U32)Rtc_Tick_ISR;
   	rINTMSK &= ~(BIT_TICK);

	// for checking tick interval
   	rGPHCON = (rGPHCON & ~(3<<26)) | (1<<26);
	rGPHDAT |= (1<<13);

    	
   	rTICNT0 |= (1<<7);	// Tick Time Interrupt Enable
	//StartStopwatch();
    	
   	while(!Uart_GetKey()) {
    		
   		while(!Tick)
   			{
 #if 0    // yym tick enable setup time check after tick disable(tick counter reset operation check)
			  if(Uart_GetKey())
   			  	{
   			  	     rTICNT0 &= ~(1<<7);
   			  	     rTICNT0 |= (1<<7);
   			  	}
			  printf("Tick cnt value = %08x\n", rTICKCNT);
#endif
   			}

		;	// Wait Tick Interrupt
		//printf("Tick cnt value = %08d\n", rTICNT0); // internal tick time counter register (s3C2443 only)
		//Print_RTC();
  		Tick=0;
    	}

	//transtime = EndStopwatch();
	//printf("%dusec\n",transtime);

	rRTCCON &= ~(1<<4);
  	rTICNT0 &= ~(1<<7);	// Tick Time Interrupt Disable
   	rINTMSK |= (BIT_TICK);
   	ClearPending(BIT_TICK);

}


void RTC_tick_CLKRST(void)
{
	int i,j;
	RTC_Init();
	//Uart_getc();
	SetResStopwatch(100000);
	//while(1)
	//{	

	transtime = 0;
	
		

	rRTCCON  = rRTCCON  & ~(0x1) &~(1<<3) | 0x1|(0<<3);            // clk counter enable, RTC Control enable
	
	rRTCCON = (rRTCCON & ~(0xf<<5)&~(0x1<<4) ) | (5<<5)|(0<<4);     //  1/32768 second tick colck
	
	printf(" rtcon = %08x\n", rRTCCON);

	j= rand()%0x100000;
	for (i=0; i<j;i++);
		
	rTICNT2 = 0;
	rTICNT0 = 0;
	rTICNT1 = 1;
		
		
  	pISR_TICK = (U32)Rtc_Tick_ISR_clkrst;
   	rINTMSK &= ~(BIT_TICK);

	// for checking tick interval
   	rGPHCON = (rGPHCON & ~(3<<26)) | (1<<26);
	rGPHDAT |= (1<<13);

    	printf("\n\n-----without clock reset----- \n\n");
   	rTICNT0 |= (1<<7);	// Tick Time Interrupt Enable
	StartStopwatch();
    	
   	while(Tick<11)
		{
	rINTMSK &= ~(BIT_TICK);
	rTICNT0 |= (1<<7);	// Tick Time Interrupt Enable
		
		}
   		
   	//printf("Tick cnt value = %08x\n", rTICKCNT);
	transtime = EndStopwatch();
	printf("-----without clock reset-----\n\n");
	
	Tick=0;
	transtime = 0;

	rRTCCON  = rRTCCON  & ~(0x1) &~(1<<3) |(0<<3)| 0x1;            // clk counter reset, RTC Control enable
	rRTCCON  = rRTCCON  & ~(0x1) &~(1<<3) |(1<<3)| 0x0;            // clk counter enable, RTC Control disable
  	rTICNT0 &= ~(1<<7);	// Tick Time Interrupt Disable
   	rINTMSK |= (BIT_TICK);
   	ClearPending(BIT_TICK);



	rINTMSK &= ~(BIT_TICK);

	printf("\n\n------After clock reset----- \n\n");
   	rTICNT0 |= (1<<7);	// Tick Time Interrupt Enable
	StartStopwatch();
    	
   	while(Tick<11)

   	{
	rINTMSK &= ~(BIT_TICK);
	rTICNT0 |= (1<<7);	// Tick Time Interrupt Enable

	}
   		
   	//printf("Tick cnt value = %08x\n", rTICKCNT);
	transtime = EndStopwatch();
	printf("------after clock reset------- \n\n");

	Tick=0;
	rRTCCON &= ~(1<<4);
  	rTICNT0 &= ~(1<<7);	// Tick Time Interrupt Disable
   	rINTMSK |= (BIT_TICK);
   	ClearPending(BIT_TICK);

//	}  //while(1)		
    	
}

void __irq Rtc_Tick_ISR_clkrst(void)
{

	rTICNT0 &= ~(1<<7);	// Tick Time Interrupt Disable
   	rINTMSK |= (BIT_TICK);
	ClearPending(BIT_TICK);

	rGPHDAT ^= (1<<13); // for test tick interval
	Tick++;

	transtime = EndStopwatch();
	printf(" reset: %dusec\n",transtime);
	

	StartStopwatch();

}


void Rtc_Alarm(void)
{
	int i;
	
    	printf("[ RTC Alarm Test for S3C2450 ]\n");

    	rRTCCON  = 0x01;                    //No reset, Merge BCD counters, 1/32768, RTC Control enable
    	rALMYEAR = TESTYEAR2 ;
    	rALMMON  = TESTMONTH2;
    	rALMDATE = TESTDATE2 ;
    	rALMHOUR = TESTHOUR2 ;
    	rALMMIN  = TESTMIN2  ;
    	rALMSEC  = TESTSEC2  ; 

		
		printf("Select alarm interrupt source  \n");
		printf("1:sec 2:min 3:hour 4:date 5:month 6:year\n");
		
		i = GetIntNum();
		rRTCALM  = (rRTCALM & ~(0x3f<<0))|(1<<(i-1)); //Year,Month,Day,Hour,Minute,Second alarm enable
		printf( " rRTCALM = %08x\n", rRTCALM);
				
		printf("After 5 sec, alarm interrupt will occur.. \n");
		printf("alarm:%2x : %2x : %2x  %2x/%2x/20%02x\n",rALMHOUR,rALMMIN,rALMSEC,rALMMON,rALMDATE,rALMYEAR);
				
		RTC_Init();
		printf("curr:%2x : %2x : %2x  %2x/%2x/20%02x\n",rBCDHOUR,rBCDMIN,rBCDSEC,rBCDMON,rBCDDATE,rBCDYEAR);	
    	
    	Alarm = 0;
	
    	pISR_RTC = (unsigned int)Rtc_Alarm_ISR;
    	
    	rRTCALM  |= (1<<6);
    
      	rRTCCON  = 0x0;                     //No reset, Merge BCD counters, 1/32768, RTC Control disable
    	rINTMSK  = ~(BIT_RTC);
		
	
	while(Alarm==0)
    	{
		if ( !(i == rBCDSEC))
		{	printf("%2x : %2x : %2x  %10s,  %2x/%2x/20%02x\n",rBCDHOUR,rBCDMIN,rBCDSEC,day[rBCDDAY],rBCDMON,rBCDDATE,rBCDYEAR);	
			i = rBCDSEC;
		}
    	}
	Alarm = 0;
	printf("Alarmed:%2x : %2x : %2x  %10s,  %2x/%2x/20%02x\n",rBCDHOUR,rBCDMIN,rBCDSEC,day[rBCDDAY],rBCDMON,rBCDDATE,rBCDYEAR);

		
	rRTCALM = 0x0; //alarm off
	rINTMSK = BIT_ALLMSK;
	
	//rRTCCON = 0x0;  //RTC  Control disable(for power consumption), 1/32768, Normal(merge), No reset}
	
}

void Tick_Count_Set(U32 count)
{
	U32 temp;

	if (count !=1) 
	{
		temp = (count-1)%32768;
	 	rTICNT2 = (count-1)/32768;
		rTICNT0 = temp/256;
		rTICNT1 = temp%256;
	}
	else
	{
		printf("time display by every 2 seconds\n");
		rTICNT2 = 0;
		rTICNT0 = 0;
		rTICNT1 = 1;
	}

}

void Rtc_Alarm_Set(void)
{
   	rRTCCON  = rRTCCON  | 0x1;		//RTC Control enable

    	rALMHOUR =rBCDHOUR;
    	rALMMIN  =rBCDMIN;
    	rALMSEC  =rBCDSEC+5;

   	printf("After 5 second, Alarm Interrupt Occur\n");

  	//rRTCCON  = rRTCCON  & ~(0x1);	//RTC Control disable
}

void Print_RTC(void)
{
	int year,month,date,hour,min,sec,weekday;

   	//rRTCCON  = rRTCCON  | 0x1;		//RTC Control enable
   		
    if(rBCDYEAR==0x99) 
       	year = 0x1999;
  	else 
       	year = 0x2000 + rBCDYEAR;
              	
	month   = rBCDMON;
	weekday = rBCDDAY;
	date    = rBCDDATE;
	hour    = rBCDHOUR;
	min     = rBCDMIN;
	sec     = rBCDSEC;

  	//rRTCCON  = rRTCCON  & ~(0x1);	//RTC Control disable
	printf("%2x : %2x : %2x  %10s,  %2x/%2x/%4x\n",hour,min,sec,day[weekday],month,date,year);
}


void RTC_SetTime(void)
{
	int year,month,date,hour,min,sec,weekday;

   	rRTCCON  = rRTCCON  | 0x1;		//RTC Control enable
   	printf("\nYear(0x00~0x99):");
	year = GetIntNum();
	printf("\nMonth(0x1~0x12):");
	month = GetIntNum();
	
	printf("\nweekday(0x1~0x7):");
	weekday = GetIntNum();
	
	printf("\nDate(0x1~0x31):");
	date = GetIntNum();
	
	printf("\nHour(0x0~0x23):");
	hour = GetIntNum();

	printf("\nMin(0x0~0x59):");
	min = GetIntNum();

	printf("\nSec(0x0~0x59):");
	sec = GetIntNum();
	printf("\n");
	rBCDYEAR = year;
       rBCDMON = month;
	rBCDDAY = weekday ;
	
	rBCDDATE = date   ;
	rBCDHOUR = hour ;
	
	rBCDMIN = min  ;
	rBCDSEC = sec ;


	rRTCCON  = rRTCCON  & ~(0x1);	//RTC Control disable

	
    if(rBCDYEAR==0x99) 
       	year = 0x1999;
  	else 
       	year = 0x2000 + rBCDYEAR;
              	
	month   = rBCDMON;
	weekday = rBCDDAY;
	date    = rBCDDATE;
	hour    = rBCDHOUR;
	min     = rBCDMIN;
	sec     = rBCDSEC;

  
	printf("%2x : %2x : %2x  %10s,  %2x/%2x/%4x\n",hour,min,sec,day[weekday],month,date,year);
}
void RTC_Init(void)
{

    rRTCCON  = rRTCCON  & ~(0xf)  | 0x1;            //No reset, Merge BCD counters, 1/32768, RTC Control enable
    
    rBCDYEAR = rBCDYEAR & ~(0xff) | TESTYEAR;
    rBCDMON  = rBCDMON  & ~(0x1f) | TESTMONTH;
    rBCDDATE = rBCDDATE & ~(0x3f) | TESTDATE;         
    rBCDDAY  = rBCDDAY  & ~(0x7)  | TESTDAY;       //SUN:1 MON:2 TUE:3 WED:4 THU:5 FRI:6 SAT:7
    rBCDHOUR = rBCDHOUR & ~(0x3f) | TESTHOUR;
    rBCDMIN  = rBCDMIN  & ~(0x7f) | TESTMIN;
    rBCDSEC  = rBCDSEC  & ~(0x7f) | TESTSEC;
    
    rRTCCON  = 0x0;             //No reset, Merge BCD counters, 1/32768, RTC Control disable    

}





void __irq Rtc_Tick_ISR(void)
{
	rGPHDAT ^= (1<<13); // for test tick interval
	ClearPending(BIT_TICK);
	Tick=1;
	//transtime = EndStopwatch();
	
	//printf("\n%dusec\n",transtime);


	printf(" RTC tick interrupt occurred!\n");
}





void __irq Rtc_Alarm_ISR(void)
{
	ClearPending(BIT_RTC);
	Alarm=1;
	printf(" RTC alarm test OK\n");
	printf("rSRCPND %x , rINTPND %x \n",rSRCPND,rINTPND);
}


/////////////////////////////////////////////////////
// autotest
//


//condition to success :
//coverage : 
bool RTC_initialize_autotest(void)
{
	int year,month,date,hour,min,sec;
	int old_sec = 0x0, i=0;
	int cntfail=0;

	year =  6;
	month= 12;
	date = 31;
	hour = 23;
	min  = 59;
	sec  = 20;
	
	rRTCCON  = rRTCCON  | 0x1;		//RTC Control enable
	
	rBCDYEAR =( ((year/10)<<4) + (year%10) );
	rBCDMON  =( ((month/10)<<4)+ (month%10));
	rBCDDATE =( ((date/10)<<4) + (date%10) );     	
	rBCDDAY  = rBCDDAY  & ~(0x7)  | 0x3;		//SUN:1 MON:2 TUE:3 WED:4 THU:5 FRI:6 SAT:7
	rBCDHOUR =( ((hour/10)<<4) + (hour%10) );
	rBCDMIN  =( ((min/10)<<4)  + (min%10)  );
	rBCDSEC  =( ((sec/10)<<4)  + (sec%10)  );     	

	rRTCCON = rRTCCON | (1<<3); //divider count init.
	rRTCCON = rRTCCON & ~(1<<3);

	rRTCCON  = rRTCCON  & ~(0x1);	//RTC Control disable

  	while (!Uart_GetKey())
  	{	
  			
  			sec = (rBCDSEC & 0x7F);
  						
  			if(sec==old_sec)
  			{
  				if(i++ == 2000000)
  				{		
	  				i = 0;
	  				printf("[]");
	  				
  				}
  			}
  			else
  			{
  				if( sec ==  old_sec+1)
  				{
  					if( ( sec     & 0xF)<10 ||
  				        ((sec>>4) & 0xF)<6  				    
  				       )
  				    {
	  					if(i++ == 2000000)
		  				{
			  				i = 0;
			  				printf("[]");		  			
		  				}		  				
		  				
		  				// 2 log at every 10min
		  				min=rBCDMIN;
		  				if( (min&0xF) == 0 && (sec==0x5 || sec == 0x35) )
		  				{
		  					AUTO_msginfo_printf("%2x:%2x:%2x  %10s,  %2x.%2x.20%02x",
		  									rBCDHOUR,rBCDMIN,rBCDSEC,day[rBCDDAY],rBCDMON,rBCDDATE,rBCDYEAR);
		  				}  	
		  				
		  				// test for during 2min
		  				if(min == 0x2) break;			
		  				
  				    }
  				    else
  				    {
  				    	AUTO_errinfo_printf("i:%d sec : 0x%2x  -- old_sec : 0x%2x", i, sec, old_sec); 
  				    	cntfail++;
  				    }
  				}
  				else
  				{
	  				if( (old_sec == 0x9 && sec == 0x10) ||
	  				    (old_sec == 0x19 && sec == 0x20) ||
	  				    (old_sec == 0x29 && sec == 0x30) ||
	  				    (old_sec == 0x39 && sec == 0x40) ||
	  				    (old_sec == 0x49 && sec == 0x50) ||
	  				    (old_sec == 0x59 && sec == 0x0)
	  				   )
	  				{
	  					if(i++ == 2000000)
		  				{
			  				i = 0;
			  				printf("[]");		  			
		  				}  
	  				}
	  				else
					{
	  				   	AUTO_errinfo_printf("i:%d sec : 0x%2x  -- old_sec : 0x%2x", i, sec, old_sec); 
	  				   	cntfail++;
	  				}  				
  				}
  			}
  			old_sec = sec;
  			
  	}	
	
	if(cntfail == 0) 	return true;
	else return false;
	
}

