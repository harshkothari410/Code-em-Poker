#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int hole_card1,hole_card2,num,money,cardnum,money_remaining;
int same1,same2,same3,same4,same5,same6,same7,color1,color2,color3,color4,color5,color6,color7;
int card3,card4,card5,card6,card7,color[7],card_array[7];
int best_comb_card[5] = {0,0,0,0,0};
int best_comb_flag,comb_flag[10]={0,0,0,0,0,0,0,0,0,0};
int which_color=0,six_color=0;
int single_pair,double_pair[2],three_kind[2],four_kind,full_house[2];
int four_color=0,three_color=0;
int straight_array[] = {1,496,826,1036,1162,1232,1267,1282,1287};
char type[30],of[3],card[30];
char a[10];
int comb_no;
int rise_decision1 = 0;
int player[600];
int bid_val[600];
char bid[600][7];
int i;
int b,c;
int bat_round=0,num_bat_round = 0;
int my_place = 0;
int deal_num,user[6],rupee[6],dealer,big_blind,small_blind,main_pot;
char stage[15];
int pre_rise_val,my_pre_rise_val=0;
int last_decision,rise_decision,rise_value;
int call_val;

void pre_flop(FILE *p);
void my_decision(int ,int,int);
void flop(FILE *);
void fourth_street(FILE *);
void fifth_street(FILE *);
void find_best_comb(int);
void comb_number();
void decision();
void show_down();

int main()
{
	
	FILE *p1,*p2,*p3,*p4;
	p1 = fopen("inputf.txt","r");
//	p2 = fopen("cards.txt","r");
	p3 = fopen("deals_money.txt","r");
	p4 = fopen("deal.txt","r");

	fscanf(p1,"%d%d%d%d",&hole_card1,&hole_card2,&num,&money);
//	printf("data from file inputf\n");
//	printf("%d %d %d %d",hole_card1,hole_card2,num,money);
	
//	fclose(p2);
	same1 = hole_card1%13;
	same2 = hole_card2%13;
	
	color1 = hole_card1/13;
	color2 = hole_card2/13;

	if(p3 == NULL)
	{
//	printf("\n\nfile not opened");
	}

	fscanf(p3,"%s%d",a,&deal_num);
	
	i=0;
	printf("\n\n");
	while(fscanf(p3,"%d%d",&b,&c)!=EOF)
	{
		user[i] = b;
		rupee[i] = c;
		//printf("\n%d\t%d",user[i],rupee[i]);
        i++;
	}
	
	if(p4==NULL)
	{
//		printf("Cant open file");
		exit(1);
	}

	fscanf(p4,"%s%d",a,&dealer);
	fscanf(p4,"%s%s",a,stage);
	fscanf(p4,"%s%d",a,&main_pot);
//	printf("\n\noutput from file deal");
//	printf("\nDealer:%d\tStage:%s\tMain_pot:%d",dealer,stage,main_pot);	
	
	money_remaining = rupee[num-1];
	money_remaining = money_remaining - money;	
	if(dealer<num)
	my_place = num - dealer ;
	else
	my_place =6 - (dealer - num) ;
	
	if(my_place == 1)
	small_blind = 1;
	
	if(my_place == 2)
	big_blind = 1;
	bat_round = 1;
	if(stage[0]=='P')
	pre_flop(p4);

	if(stage[1]=='l')
	flop(p4);
	
	if(stage[1]=='o')
	fourth_street(p4);
	
	if(stage[1]=='i')
	fifth_street(p4);
	
	if(stage[0] == 'S')
	show_down();


fclose(p3);
return(0);

}

// function for pre flop stage

void pre_flop(FILE *p)
{
	char temp[10];
	FILE *help;
	help = fopen("help410.txt","r");
	if(help == NULL)
	goto h;
		fscanf(help,"%d",&num_bat_round);
//	printf("pre bat round:%d",num_bat_round);
	fclose(help);
	
h:	while(1)
	{
		fscanf(p,"%s",temp);
		if(temp[0]=='P')
		break;
	}
//	printf("\n\nmoney baki:%d\n\n",money_remaining);
	
	//fscanf(help,"%d",&num_bat_round);
//	printf("pre bat round:%d",num_bat_round);
	//fclose(help);
	
	help = fopen("help410.txt","w");
	if(num_bat_round != 0)
	{
		my_place = my_place + (6*num_bat_round);
	}
	for(i=0;i<my_place-1;i++)
	{
		fscanf(p,"%d%s%d",&player[i],bid[i],&bid_val[i]);
//		printf("\n%d\t\t%s %d",player[i],bid[i],bid_val[i]);
	}
	if(num == 1)
	call_val = bid_val[5];
	else
	call_val = bid_val[my_place-2];
//	printf("\ncall val:%d",call_val);
	rise_decision = 0;
	for(i=0;i<6;i++)
	{
		if(bid[i][0] == 'R')
		{
			if(bid_val[i] != 5 && bid_val[i] != 10)
			{
				rise_decision = 1;
				pre_rise_val = bid_val[i];
			}
		}
	}
	
	if(same1>0)
	{
		last_decision = 1;
		if(rise_decision == 1)
		last_decision = 0;
		
	}
	
	if(same1>5 || same2>5)
	{
		last_decision = 1;
		if(rise_decision == 1 && pre_rise_val<int(money_remaining*0.03))
		last_decision = 1;
		if(rise_decision == 1 && pre_rise_val>=int(money_remaining*0.03))
		last_decision = 0;
		 
	}
	
	if(same1>9 && same2>9)
	{
		last_decision = 1;
		if(rise_decision == 1 && pre_rise_val<int(money_remaining*0.04))
		last_decision = 1;
		if(rise_decision == 1 && pre_rise_val>=int(money_remaining*0.04))
		last_decision = 0;
	}
	
	if(same1 == same2)
	{
		if(same1 == 0 || same1 == 12 || same1 == 11 || same1 == 10)
		{
			last_decision = 2;
			if(rise_decision == 1 )//my_pre_rise_val
			{
				last_decision = 1; //function for rise value
			}
			
		}
		else
		{
			last_decision = 1;
			if(rise_decision == 1 && pre_rise_val<int(money_remaining*0.04))//my_pre_rise_val
			{
				last_decision = 1; //function for rise value
			}
			if(rise_decision == 1 && pre_rise_val>=int(money_remaining*0.04))
			last_decision = 0;
			
		}
	}
	
	if(color1 == color2)
	{
		last_decision = 1;
		if(rise_decision == 1 && pre_rise_val<int(money_remaining*0.03))//my_pre_rise_val
		{
			last_decision = 1; //function for rise value
		}
		if(rise_decision == 1 && pre_rise_val>=int(money_remaining*0.03))
		last_decision = 0;
	}
//	printf("\nrd:%d",rise_decision);
//	printf("\nmy_place:%d,decision:%d",my_place,last_decision);
	if(num_bat_round == 0)
	{
		if(big_blind == 1)
		my_decision(2,10,call_val);
		if(small_blind == 1)
		my_decision(2,5,call_val);
	}
	rise_value = 50;
	if(rise_value<= call_val)
	rise_value  = rise_value + call_val;
	my_decision(last_decision,rise_value,call_val);
	num_bat_round++;
	bat_round = num_bat_round;
//	fseek(help);
	fprintf(help,"%d",bat_round);
	fclose(help);
}

// function for flop stage

void flop(FILE *p)
{
	FILE *help;
	help = fopen("help411.txt","r");
	char temp[10];
		if(help == NULL)
	goto h1;
		bat_round = 1;
	fscanf(help,"%d",&num_bat_round);
//	printf("pre bat round:%d",num_bat_round);
	fclose(help);

	
h1:
	while(1)
	{
		fscanf(p,"%s",temp);
		if(temp[1]=='l')
		break;
	}
//	printf("\n\n%d",ftell(p));
	fscanf(p,"%d%d%d",&card3,&card4,&card5);
//	printf("\nNew 3 cards:");
//	printf("\n%d %d %d",card3,card4,card5);
	
	//findind color n card num between 1 to 13..
	
	same3 = card3 % 13;
	same4 = card4 % 13;
	same5 = card5 % 13;
	
	color3 = card3 / 13;
	color4 = card4 / 13;
	color5 = card5 / 13;
	
	//making card array
	if(same1 == 0)
	same1 = 13;
	if(same2 == 0)
	same2 = 13;
	if(same3 == 0)
	same3 = 13;
	if(same4 == 0)
	same4 = 13;
	if(same5 == 0)
	same5 = 13;
	
	card_array[0] = same1;
	card_array[1] = same2;
	card_array[2] = same3;
	card_array[3] = same4;
	card_array[4] = same5;

	// making color array
	
	color[0] = color1;	// value of array, 0 for spade, 1 for club, 2 for heart, 3 for diamond
	color[1] = color2;
	color[2] = color3;
	color[3] = color4;
	color[4] = color5;
	find_best_comb(5);
//	bat_round = 1;
//	fscanf(help,"%d",&num_bat_round);
//	printf("pre bat round:%d",num_bat_round);
//	fclose(help);
	
	help = fopen("help411.txt","w");
	if(num_bat_round != 0)
	{
		my_place = my_place + (6*num_bat_round);
	}
	
	
	for(i=0;i<my_place-1;i++)
	{
		fscanf(p,"%d%s%d",&player[i],bid[i],&bid_val[i]);
		if(bid[i][0] == '-')
		{
			bid_val[i] = bid_val[i-1];
			fseek(p,-0L,SEEK_CUR);
		}
		//printf("\npointer:%d",ftell(p));
//		printf("\n%d\t\t%s %d",player[i],bid[i],bid_val[i]);
	}
	
	if(num == 1)
	call_val = bid_val[5];
	else
	call_val = bid_val[my_place-2];
//	printf("\ncall val:%d",call_val);
	rise_decision = 0;
	for(i=0;i<6;i++)
	{
		if(bid[i][0] == 'R')
		{
			if(bid_val[i] != 5 && bid_val[i] != 10)
			{
				rise_decision1 = 1;
				pre_rise_val = bid_val[i];
			}
		}
	}
	comb_number();
	decision();
	
	
	my_decision(last_decision,rise_value,call_val);
	
	num_bat_round++;
	bat_round = num_bat_round;
	
	fprintf(help,"%d",bat_round);
	fclose(help);
}



void fourth_street(FILE *p)
{
	char temp[20];
	FILE *help;
	help = fopen("help412.txt","r");
		if(help == NULL)
	goto h2;
		bat_round = 1;
	fscanf(help,"%d",&num_bat_round);
//	printf("pre bat round:%d",num_bat_round);
	fclose(help);

	
h2:

	while(1)
	{
		fscanf(p,"%s",temp);
		if(temp[1]=='l')
		break;
	}
//	printf("\n\n%d",ftell(p));
	fscanf(p,"%d%d%d",&card3,&card4,&card5);
//	printf("\nNew 3 cards:");
//	printf("\n%d %d %d",card3,card4,card5);
	
	//findind color n card num between 1 to 13..
	
	same3 = card3 % 13;
	same4 = card4 % 13;
	same5 = card5 % 13;
	
	color3 = card3 / 13;
	color4 = card4 / 13;
	color5 = card5 / 13;
	
	if(same1 == 0)
	same1 = 13;
	if(same2 == 0)
	same2 = 13;
	if(same3 == 0)
	same3 = 13;
	if(same4 == 0)
	same4 = 13;
	if(same5 == 0)
	same5 = 13;
	//making card array
	
	card_array[0] = same1;
	card_array[1] = same2;
	card_array[2] = same3;
	card_array[3] = same4;
	card_array[4] = same5;

	// making color array
	
	color[0] = color1;	// value of array, 0 for spade, 1 for club, 2 for heart, 3 for diamond
	color[1] = color2;
	color[2] = color3;
	color[3] = color4;
	color[4] = color5;
	while(1)
	{
		fscanf(p,"%s",temp);
		if(temp[1]=='o')
		break;
	}
//	printf("Hello\n\n%d",ftell(p));
	fscanf(p,"%d",&card6);
//	printf("\ncard 6:%d\n",card6);
	same6 = card6%13;
	color6 = card6/13;
	
	if(same6 == 0)
	same6 = 13;
	card_array[5] = same6;
	color[5] = color6;
//	printf("\n\nCards:\n");
	for(i=0;i<6;i++)
//	printf("%d\t",card_array[i]);
	
	find_best_comb(6);
	
	
//	fscanf(help,"%d",&num_bat_round);
//	printf("pre bat round:%d",num_bat_round);
//	fclose(help);
	
	help = fopen("help412.txt","w");
	
	if(num_bat_round != 0)
	{
		my_place = my_place + (6*num_bat_round);
	}

	for(i=0;i<my_place-1;i++)
	{
		fscanf(p,"%d%s%d",&player[i],bid[i],&bid_val[i]);
		if(bid[i][0] == '-')
		{
			bid_val[i] = bid_val[i-1];
			fseek(p,-0L,SEEK_CUR);
		}
//		printf("\n%d\t\t%s %d",player[i],bid[i],bid_val[i]);
	}
	
	if(num == 1)
	call_val = bid_val[5];
	else
	call_val = bid_val[my_place-2];
//	printf("\ncall val:%d",call_val);
	rise_decision = 0;
	for(i=0;i<6;i++)
	{
		if(bid[i][0] == 'R')
		{
			if(bid_val[i] != 5 && bid_val[i] != 10)
			{
				rise_decision1 = 1;
				pre_rise_val = bid_val[i];
			}
		}
	}
	
	comb_number();
	decision();
	my_decision(last_decision,rise_value,call_val);
	
	num_bat_round++;
	bat_round = num_bat_round;
	
	fprintf(help,"%d",bat_round);
	fclose(help);
}


void fifth_street(FILE *p)
{
	char temp[20];
	FILE *help;
	help = fopen("help413.txt","r");
			if(help == NULL)
	goto h3;
		bat_round = 1;
	fscanf(help,"%d",&num_bat_round);
//	printf("pre bat round:%d",num_bat_round);
	fclose(help);

	
h3:

	
	while(1)
	{
		fscanf(p,"%s",temp);
		if(temp[1]=='l')
		break;
	}
//	printf("\n\n%d",ftell(p));
	fscanf(p,"%d%d%d",&card3,&card4,&card5);
//	printf("\nNew 3 cards:");
//	printf("\n%d %d %d",card3,card4,card5);
	
	//findind color n card num between 1 to 13..
	
	same3 = card3 % 13;
	same4 = card4 % 13;
	same5 = card5 % 13;
	
	color3 = card3 / 13;
	color4 = card4 / 13;
	color5 = card5 / 13;
	
	if(same1 == 0)
	same1 = 13;
	if(same2 == 0)
	same2 = 13;
	if(same3 == 0)
	same3 = 13;
	if(same4 == 0)
	same4 = 13;
	if(same5 == 0)
	same5 = 13;
	
	//making card array
	
	card_array[0] = same1;
	card_array[1] = same2;
	card_array[2] = same3;
	card_array[3] = same4;
	card_array[4] = same5;

	// making color array
	
	color[0] = color1;	// value of array, 0 for spade, 1 for club, 2 for heart, 3 for diamond
	color[1] = color2;
	color[2] = color3;
	color[3] = color4;
	color[4] = color5;
	while(1)
	{
		fscanf(p,"%s",temp);
		if(temp[1]=='o')
		break;
	}
	
	fscanf(p,"%d",&card6);
//	printf("\ncard 6:%d\n",card6);
	same6 = card6%13;
	color6 = card6/13;
	if(same6 == 0)
	same6 = 13;
	
	card_array[5] = same6;
	color[5] = color6;
	
	while(1)
	{
		fscanf(p,"%s",temp);
		if(temp[2]=='f')
		break;
	}
	fscanf(p,"%d",&card7);
	same7 = card7%13;
	color7 = card7/13;
	if(same7 == 0)
	same7 = 13;
	
	card_array[6] = same7;
	color[6] = color7;
	
//	fscanf(help,"%d",&num_bat_round);
//	printf("pre bat round:%d",num_bat_round);
//	fclose(help);
	
	help = fopen("help413.txt","w");
	
	if(num_bat_round != 0)
	{
		my_place = my_place + (6*num_bat_round);
	}
	for(i=0;i<my_place-1;i++)
	{
		fscanf(p,"%d%s%d",&player[i],bid[i],&bid_val[i]);
		if(bid[i][0] == '-')
		{
			bid_val[i] = bid_val[i-1];
			fseek(p,-0L,SEEK_CUR);
		}
//		printf("\n%d\t\t%s %d",player[i],bid[i],bid_val[i]);
	}
	
	if(num == 1)
	call_val = bid_val[5];
	else
	call_val = bid_val[my_place-2];
//	printf("\ncall val:%d",call_val);
	rise_decision = 0;
	for(i=0;i<6;i++)
	{
		if(bid[i][0] == 'R')
		{
			if(bid_val[i] != 5 && bid_val[i] != 10)
			{
				rise_decision1 = 1;
				pre_rise_val = bid_val[i];
			}
		}
	}
	find_best_comb(7);
	comb_number();
//	printf("\ncomb no:%d\n",comb_no);
	decision();
	my_decision(last_decision,rise_value,call_val);
	
	num_bat_round++;
	bat_round = num_bat_round;
	
	fprintf(help,"%d",bat_round);
	fclose(help);
}

void find_best_comb(int n)
{
	int color_temp[4]={
		0,0,0,0
	};
	int fc,b,j;
	
	for(j=0;j<n;j++)
	{
		for(i=0;i<n-1;i++)
		{
			if(card_array[i+1]<=card_array[i])  // here b is temp variable for swaping
			{
				b = card_array[i];
				card_array[i] = card_array[i+1];
				card_array[i+1] = b;
				fc = color[i];
				color[i] = color[i+1];
				color[i+1] = fc;
			}
		}
	}	

	for(i=0;i<=n-1;i++)
	{
		switch(color[i])
		{
			case 0:
			{
				color_temp[0]++;
				break;
			}
			
			case 1:
			{
				color_temp[1]++;
				break;
			}
			
			case 2:
			{
				color_temp[2]++;
				break;
			}
			
			case 3:
			{
				color_temp[3]++;
			}
		}
	}
	
	for(i=0;i<=3;i++)
	{
		switch(color_temp[i])
		{
			case 3:
			{
				three_color = 1;
				break;
			}
			
			case 4:
			{
				four_color = 1;
				break;
			}
			
			case 5:
			{
				comb_flag[4] = 1;
				which_color = i;
				break;
			}
			
			case 6:
			{
				six_color = 1;
				comb_flag[4] = 1;
				which_color = i;
				break;
			}
			
			case 7:
			{
				six_color = 1;
				comb_flag[4] = 1;
				which_color = i;
				break;
			}
			default:
			break;
			
		}	
	}
	
	
//	printf("color:%d",which_color);
	//printf("\n\ncolor_flag:%d %d %d",three_color,four_color,flush_flag);


	
	

	
	
		b=0;
		c=0;
		fc = 0;
	for(i=0;i<=n;i++)
	{
		if(card_array[i+1]!=card_array[i])
		{
			for(j=0;j<=n;j++)
			{
				if(card_array[i]==card_array[j])
				{
					b=b+1;
				}
			}
//			printf("\n\nthe %d is enter %d times",card_array[i],b);
			
			switch(b)
			{
				case 1:
				{
					//printf("\nno match");
					break;
				}
				case 2:
				{
					comb_flag[8] ++;
					if(comb_flag[8] == 2)
					{
						comb_flag[8] = 0;
						comb_flag[7] = 1;
						double_pair[1] = card_array[i];
						double_pair[0] = single_pair;
						//printf("\ndouble pair:%d %d",double_pair[0],double_pair[1]);
					}
					else
					{
						single_pair = card_array[i];
					//	printf("\ndouble:%d",single_pair);
					}
					break;
				}
		
				case 3:
				{
					comb_flag[6] ++ ;
					three_kind[c] = card_array[i];
					//printf("\ntriple:%d",three_kind[c]);
					c++;
					
					break;
				}
		
				case 4:
				{
					comb_flag[2]++ ;
					four_kind = card_array[i];
				//	printf("\nquad:%d",four_kind);
					
					break;
				}
			}
			b=0;
		}
	}
//	printf("hello:%d",comb_flag[5]);
	
	// for straight
	
	fc = card_array[0];
	b=0;
	for(i=0;i<n-1;i++)
	{
		fc++;
		if(fc == card_array[i+1])
		{
			b++;
		}
		else
		{
			b=0;
			fc = card_array[i+1];
		}
		if(b==5 || b==4 || b==6)
		{
		comb_flag[5] = 1;
//		printf("\n\nnisarg\n\n");
		}
	}
	

	// finding straight flush
	if(comb_flag[4] == 1 && comb_flag[5] == 1)
	{
		
		comb_flag[1] = 1;
		comb_flag[4] = 0;
		comb_flag[5] = 0;
	}
	
	
	// for full house
	if( comb_flag[6] == 1  || comb_flag[6] == 2)
	{
		if(comb_flag[7] == 1 || comb_flag[8] == 1)
		{
		comb_flag[3] = 1;
	//	comb_flag[8] = 0;
		comb_flag[6] = 0;
		full_house[0] = three_kind[0];		// 0 index for 3 card,1 for 2 cards
		if(comb_flag[8] == 1)
		{
		full_house[1] = single_pair;
		
		}
		else
		full_house[1] = double_pair[1];
		}
	
		if(comb_flag[6]==2)
		{
			comb_flag[3] = 1;
			comb_flag[6] = 0;
			full_house[0] = three_kind[1];
			full_house[1] = three_kind[0];
			//printf("\n\nharsh:%d %d",three_kind[0],three_kind[1]);
		}
	}	
	
	//finding best flag
	
	best_comb_flag = 0;
	
	for(i=0;i<10;i++)
	{
		if(comb_flag[i]==1 || comb_flag[i]==2)
		{
			break;
		}
		best_comb_flag ++;
	}
	if(best_comb_flag == 10)
	{
		comb_flag[9] = 1;
		best_comb_flag = 9;
	}
	
	// printing flags and cards
//	printf("\n");
//	printf("Cards:");
//	for(i=0;i<n;i++)
//	{
//		printf("%d\t",card_array[i]);
//	}
//	printf("\n");
//	printf("Color:");
//	for(i=0;i<n;i++)
//	{
//		printf("%d\t",color[i]);
//	}
	
	
//	printf("\nflags:\n");
//	for(i=0;i<10;i++)
//	{
//		printf("%d\t%d\n",i,comb_flag[i]);
//	}
	
//	printf("\nbest_flag:%d\n",best_comb_flag);
	
	
	// finding best 5 cards
	
	b=0;
	switch(best_comb_flag)
	{
		case 0:
		{
			best_comb_card[0] = 9;
			best_comb_card[1] = 10;
			best_comb_card[2] = 11;
			best_comb_card[3] = 12;
			best_comb_card[4] = 13;
			
		}
		break;
		
		case 1:
		{
			if(card_array[5]-card_array[1] == 4)
			{
				for(i=5;i>=1;i--)
				best_comb_card[i-1] = card_array[i];
			}
			
			if(card_array[4]-card_array[0] == 4)
			{
				for(i=4;i>=0;i--)
				best_comb_card[i] = card_array[i];
			}
			b=4;
			if(card_array[5]-card_array[0] == 5)
			{
				for(i=5;i>=1;i--)
				{
					if(which_color == color[i])	
					{
						best_comb_card[b] = card_array[i];
						b--;
					}
					
				}
			}
			
			if(card_array[5]-card_array[0] == 4)
			{
				b=0;
				for(i=0;i<=5;i++)
				{
					if(card_array[0] == card_array[i+1])
					{
						card_array[0]--;
					}
					else
					{
						best_comb_card[b] = card_array[i];
						b++;
					}
					card_array[0]++;
				}
				
			}
		}
		break;
		
		case 2:
		{
			for(i=n-1;i>=0;i--)
			{
				if(card_array[i] != four_kind)
				{
					best_comb_card[4] = card_array[i];
					break;
				}
			}
			for(i=0;i<4;i++)
			{
				best_comb_card[i] = four_kind;
			}
			
		}
		break;
	
		case 3:
		{
			for(i=0;i<3;i++)
			best_comb_card[i] = full_house[0];
			for(i=3;i<5;i++)
			best_comb_card[i] = full_house[1];
			
		}
		break;
		
		case 4:
		{
			
			if(six_color == 1)
			{
				
				for(i=n-1;i>=n-5;i--)
				best_comb_card[i-1] = card_array[i];
			}
			b=4;
			for(i=n-1;i>=0;i--)
			{
				if(which_color == color[i])
				{
					best_comb_card[b] = card_array[i];
//					printf("hi");
					b--;
				}
			}
		}
		break;
		
		case 5:
		{
			if(card_array[5]-card_array[1] == 4)
			{
				for(i=5;i>=1;i--)
				best_comb_card[i-1] = card_array[i];
			}
			
			if(card_array[4]-card_array[0] == 4)
			{
				for(i=4;i>=0;i--)
				best_comb_card[i] = card_array[i];
			}
			
			if(card_array[5]-card_array[0] == 5)
			{
				for(i=5;i>=1;i--)
				best_comb_card[i-1] = card_array[i];
			}
			
			if(card_array[5]-card_array[0] == 4)
			{
				b=0;
				for(i=0;i<=5;i++)
				{
					if(card_array[0] == card_array[i+1])
					{
						card_array[0]--;
					}
					else
					{
						best_comb_card[b] = card_array[i];
						b++;
					}
					card_array[0]++;
				}
				
			}
		}
		break;
	
		case 6:
		{
			for(i=n-1;i>=0;i--)
			{
				if(card_array[i] != three_kind[0])
				{
					b++;
					if(b==1)
					best_comb_card[4] = card_array[i];
					
					if(b==2)
					{
						best_comb_card[3] = card_array[i];
						break;
					}
				}
			}
			for(i=0;i<3;i++)
			best_comb_card[i] = three_kind[0];
			
			
		}
		break;
		
		case 7:
		{
			for(i=n-1;i>=0;i--)
			{
				if((double_pair[1] != card_array[i]))
				{
					
					if( (card_array[i] != double_pair[0]))
					{	
						
						best_comb_card[4] = card_array[i];
						break;
					}
				}
			}
			
			if(double_pair[0]>double_pair[1])
			{
				best_comb_card[0] = double_pair[1];
				best_comb_card[1] = double_pair[1];
				best_comb_card[2] = double_pair[0];
				best_comb_card[3] = double_pair[0];
			}
			else
			{
				best_comb_card[0] = double_pair[0];
				best_comb_card[1] = double_pair[0];
				best_comb_card[2] = double_pair[1];
				best_comb_card[3] = double_pair[1];
			}
			
		}
		break;
	
		case 8:
		{
			for(i=n-1;i>=0;i--)
			{
				if(card_array[i] != single_pair)
				{
					b++;
					if(b==1)
					best_comb_card[4] = card_array[i];
				
					if(b==2)
					best_comb_card[3] = card_array[i];
					
					if(b==3)
					{
						best_comb_card[2] = card_array[i];
						break;
					}
				}
			}
			best_comb_card[0] = single_pair;
			best_comb_card[1] = single_pair;
			
		}
		break;
		
		case 9:
		{
			b = 4;
			for(i=n-1;i>=n-5;i--)
			{
				best_comb_card[b] = card_array[i];
				b--;
			}
			
		}
		break;
	} 
	
//	printf("\nbest 5 cards:\n");
//	for(i=0;i<5;i++)
//	printf("%d\t",best_comb_card[i]);
}


void comb_number()
{
	int k,l,m,n,j;
	int p,q,r,s,t;
	switch(best_comb_flag)
	{
		case 0:
		comb_no = 0;
		break;
		
		case 1:
		comb_no = 0;
		break;
		
		case 2:
		{
			for(i=1;i<=13;++i)
			{
			for(j=1;j<=13;++j)
			{
				for(k=1;k<=13;++k)
				{
					for(l=1;l<=13;++l)
					{
						for(m=1;m<=13;++m)
						{
							if(i==j && j==k && k==l && m!=i)
							{
							++comb_no;
							if(best_comb_card[0] == i && best_comb_card[1] == j && best_comb_card[2] == k && best_comb_card[3] == l && best_comb_card[4] == m)
							goto end;
							}
						}
					}
				}
			}
			}
	
		}
		break;
		
		case 3:
		{
			for(i=1;i<=13;++i)
			{
			for(j=1;j<=13;++j)
			{
			for(k=1;k<=13;++k)
			{
				for(l=1;l<=13;++l)
				{
					for(m=1;m<=13;++m)
					{
						if(i==j && j==k && l!=i && l==m)
						{
							++comb_no;
							if(best_comb_card[0] == i && best_comb_card[1] == j && best_comb_card[2] == k && best_comb_card[3] == l && best_comb_card[4] == m)
							goto end;
						}
					}
				}
			}
			}
			}

		} 
		break;
		
		case 4:
		comb_no = 0;
		break;
		
		case 5:
		{
			p = best_comb_card[0];
			comb_no = straight_array[p-1];
		}
		break;
		
		case 6:
		{
			for(i=1;i<=13;++i)
			{
			for(j=1;j<=13;++j)
			{
			for(k=1;k<=13;++k)
			{
				for(l=1;l<=13;++l)
				{
					for(m=1;m<=13;++m)
					{
						if(i==j && j==k && l!=i && l<m && m!=i)
						{
							++comb_no;
							if(best_comb_card[0] == i && best_comb_card[1] == j && best_comb_card[2] == k && best_comb_card[3] == l && best_comb_card[4] == m)
							goto end;
							
						}
					}
				}
			}
			}
			}
		}
		break;
		
		case 7:
		{
			for(i=1;i<=13;++i)
			{
			for(j=1;j<=13;++j)
			{
			for(k=1;k<=13;++k)
			{
				for(l=1;l<=13;++l)
				{
					for(m=1;m<=13;++m)
					{
						if(i==j && k>i && k==l && m!=i && m!=k)
						{
							++comb_no;
							if(best_comb_card[0] == i && best_comb_card[1] == j && best_comb_card[2] == k && best_comb_card[3] == l && best_comb_card[4] == m)
							goto end;
						}
					}
				}
			}
			}
			}

		}
		break;
		
		case 8:
		{
			for(i=1;i<=13;++i)
			{
			for(j=1;j<=13;++j)
			{
			for(k=1;k<=13;++k)
			{
				for(l=1;l<=13;++l)
				{
					for(m=1;m<=13;++m)
					{
						if(i==j && k!=i && k<l && l!=i && l<m && m!=i)
						{
							++comb_no;
							if(best_comb_card[0] == i && best_comb_card[1] == j && best_comb_card[2] == k && best_comb_card[3] == l && best_comb_card[4] == m)
							goto end;
						}
					}
				}
			}
			}
			}

		}
		break;
		
		case 9:
		{
			for(i=1;i<=9;++i)
			{
			for(j=1;j<=10;++j)
			{
			for(k=1;k<=11;++k)
			{
				for(l=1;l<=12;++l)
				{
					for(m=1;m<=13;++m)
					{
							p=i;
							q=j;
							r=k;
							s=l;
							t=m;
							if(p>q || q>r || r>s || s>t || p==q || p==r || p==s || p==t || q==r || q==s || q==t || r==s || r==t || s==t)
							{
								printf("");	
							}
							else
							{
								++comb_no;
								if(best_comb_card[0] == i && best_comb_card[1] == j && best_comb_card[2] == k && best_comb_card[3] == l && best_comb_card[4] == m)
								goto end;
												
							}
					}	
				}	
			}	
			}
			}

		}
		break;
		
	}

end:for(i=0;i<3;i++);
}

void decision()
{
	int temp1,temp2;
	int rise1;
	int abc[10] = {
		1,1,201,151,121,101,101,51,51,1
	};
	
	int royalflush[]={
	0,0,2,2,200
	};

	int straightflush[]={
	0,0,2,2,200
	};

	int fourofkind[][5]={
	1,12,2,2,120,
	13,24,2,2,120,
	25,36,2,2,120,
	37,48,2,2,120,
	49,60,2,2,120,
	61,72,2,2,120,
	73,84,2,2,120,
	85,96,2,2,120,
	97,108,2,2,120,
	109,120,2,2,120,
	121,132,2,2,120,
	133,144,2,2,120,
	145,156,2,2,120 
	};

	int fullhouse[][5]={
	1,12,2,2,120,
	13,24,2,2,120,
	25,36,2,2,120,
	37,48,2,2,120,
	49,60,2,2,120,
	61,72,2,2,120,
	73,84,2,2,120,
	85,96,2,2,120,
	97,108,2,2,120,
	109,120,2,2,120,
	121,132,2,2,120,
	133,144,2,2,120,
	145,156,2,2,120 
	};

	int flush1[]={
	0,0,2,1,80
	};


	int straight1[][5]={
	0,1,2,1,70,
	0,9,2,1,70,
	0,496,2,1,70,
	0,826,2,1,70,
	0,1036,2,1,70,
	0,1162,2,1,70,
	0,1232,2,1,70,
	0,1267,2,1,70,
	0,1282,2,1,70,
	0,1287,2,1,70
	};

	int threeofkind[][5]={
	1,462,2,1,50,
	463,660,2,1,50,
	661,726,2,2,50,
	727,792,2,2,50,
	793,858,2,2,50
	};


	int twopair[][5]={


	/* ace-king */

	111,132,1,1,0,
	232,253,1,1,0,
	342,363,1,1,0,
	441,462,1,1,0,
	529,550,1,1,0,
	606,627,1,1,0,
	672,693,1,1,0,
	727,748,1,1,0,
	771,792,2,1,30,
	804,858,2,1,30,

	/* queen */

	100,110,1,1,0,
	221,231,1,1,0,
	331,341,1,1,0,
	430,440,1,1,0,
	518,528,1,1,0,
	595,605,1,1,0,
	661,671,1,1,0,
	716,726,1,1,0,
	760,770,2,1,20,
	0,0,1,1,0,
	
	1,858,1,1,0
	};

	int onepair[][5]={
	1,1980,1,1,0,	
	1981,2420,1,1,0,
	2421,2640,1,1,0,	
	2641,2860,1,1,0
	};
	
	int highcard[][5]={
	2,8,1,0,0,
	10,495,1,0,0,
	497,825,1,0,0,
	827,1035,1,0,0,
	1037,1161,1,0,0,
	1163,1231,1,0,0,
	1233,1266,1,0,0,
	1268,1281,1,0,0,
	1283,1286,1,0,0
	};
	
	if(money_remaining <=1000)
	{
		for(i=0;i<10;i++)
		abc[i] = abc[i]/2;
	}
	if(money_remaining > 1000 && money_remaining<2500)
	{
		for(i=0;i<10;i++)
		abc[i] = abc[i];
	}
	if(money_remaining <4000 && money_remaining>=2500)
	{
		for(i=0;i<10;i++)
		abc[i] = abc[i]*2;
	}
	if(money_remaining >4000 )
	{
		for(i=0;i<10;i++)
		abc[i] = abc[i]/3;
	}
	
	last_decision = 0;
	rise_value = 0;
	rise_decision = 0;
	temp2 = 0;
	temp1 = 0;
	switch(best_comb_flag)
	{
		case 0:
		{
			last_decision = royalflush[2];
			rise_decision = royalflush[3];
			rise_value = royalflush[4];
			if(rise_value<call_val || rise_value<pre_rise_val)
			{
				rise_value = call_val+rise_value;	
			}
			
			if(rise_value>money_remaining)
			{
				rise_value = money_remaining;
			}
			
		}
		break;
		
		case 1:
		{
			last_decision = straightflush[2];
			rise_decision = straightflush[3];
			rise_value = straightflush[4];
			
			if(rise_value<call_val || rise_value<pre_rise_val)
			{
				rise_value = call_val+rise_value;	
			}
			
			if(rise_value>money_remaining)
			{
				rise_value = money_remaining;
			}
			rise1 = rise_value - call_val;
		}
		break;
		
		case 2:
		{
			for(i=0;i<14;i++)
			{
				
				temp1 = fourofkind[i][0];
				temp2 = fourofkind[i][1];
			
				if(temp1 <= comb_no && temp2 >= comb_no)
				{
					
					last_decision = fourofkind[i][2];
					rise_decision = fourofkind[i][3];
					rise_value = fourofkind[i][4];
					
					if(rise_decision1 == 1)
					{
						last_decision = rise_decision;
					}
					
					if(rise_value<call_val || rise_value<pre_rise_val)
					{
						rise_value = call_val+rise_value;	
					}
				
					if(rise_value>money_remaining)
					{
						rise_value = money_remaining;
					}
		rise1 = rise_value - call_val;			
					break;
				}
				
				
				
			}
		}
		break;
		
		case 3:
		{
			for(i=0;i<14;i++)
			{
				
				temp1 = fullhouse[i][0];
				temp2 = fullhouse[i][1];
			
				if(temp1 <= comb_no && temp2 >= comb_no)
				{
					
					last_decision = fullhouse[i][2];
					rise_decision = fullhouse[i][3];
					rise_value = fullhouse[i][4];
					if(rise_decision1 == 1)
					{
						last_decision = rise_decision;
					}
					
					if(rise_decision == 1 || last_decision == 1)
					{
						if(call_val<abc[3])
						last_decision = 1;
						else
						last_decision = 0;
					}
					
					if(rise_value<call_val || rise_value<pre_rise_val)
					{
						rise_value = call_val+rise_value;	
					}
				
					if(rise_value>money_remaining)
					{
						rise_value = money_remaining;
					}
					rise1 = rise_value - call_val;
					break;
				}
				
			}
		}
		break;
		
		case 4:
		{
			last_decision = flush1[2];
			rise_decision = flush1[3];
			rise_value = flush1[4];
			
			if(rise_decision1 == 1)
					{
						last_decision = rise_decision;
					}
			
			if(rise_decision == 1 || last_decision == 1)
					{
						if(call_val<abc[4])
						last_decision = 1;
						else
						last_decision = 0;
					}
					
					if(rise_value<call_val || rise_value<pre_rise_val)
					{
						rise_value = call_val+rise_value;	
					}
				
					if(rise_value>money_remaining)
					{
						rise_value = money_remaining;
					}
					rise1 = rise_value - call_val;
		}
		break;
		
		case 5:
		{
			for(i=0;i<14;i++)
			{
				
				
				temp2 = straight1[i][1];
			
				if(temp2 == comb_no)
				{
					
					last_decision = straight1[i][2];
					rise_decision = straight1[i][3];
					rise_value = straight1[i][4];
					
					if(rise_decision1 == 1)
					{
						last_decision = rise_decision;
					}
					
					if(rise_decision == 1 || last_decision == 1)
					{
						if(call_val<abc[5])
						last_decision = 1;
						else
						last_decision = 0;
					}
					
					if(rise_value<call_val || rise_value<pre_rise_val)
					{
						rise_value = call_val+rise_value;	
					}
				
					if(rise_value>money_remaining)
					{
						rise_value = money_remaining;
					}
					rise1 = rise_value - call_val;
					break;
				}
				
			}
		}
		break;
		
		case 6:
		{
			for(i=0;i<14;i++)
			{
				
				temp1 = threeofkind[i][0];
				temp2 = threeofkind[i][1];
			
				if(temp1 <= comb_no && temp2 >= comb_no)
				{
					
					last_decision = threeofkind[i][2];
					rise_decision = threeofkind[i][3];
					rise_value = threeofkind[i][4];
					
					if(rise_decision1 == 1)
					{
						last_decision = rise_decision;
					}
					
					if(rise_decision == 1 || last_decision == 1)
					{
						if(call_val<abc[6])
						last_decision = 1;
						else
						last_decision = 0;
					}
					
					if(rise_value<call_val || rise_value<pre_rise_val)
					{
						rise_value = call_val+rise_value;	
					}
				
					if(rise_value>money_remaining)
					{
						rise_value = money_remaining;
					}
					rise1 = rise_value - call_val;
					break;
				}
				
			}
		}
		break;
		
		case 7:
		{
			for(i=0;i<34;i++)
			{
				
				temp1 = twopair[i][0];
				temp2 = twopair[i][1];
			
				if(temp1 <= comb_no && temp2 >= comb_no)
				{
					
					last_decision = twopair[i][2];
					rise_decision = twopair[i][3];
					rise_value = twopair[i][4];
					
					if(rise_decision1 == 1)
					{
						last_decision = rise_decision;
					}
					
					if(rise_decision == 1 || last_decision == 1)
					{
						if(call_val<abc[7])
						last_decision = 1;
						else
						last_decision = 0;
					}
					
					if(rise_value<call_val || rise_value<pre_rise_val)
					{
						rise_value = call_val+rise_value;	
					}
				
					if(rise_value>money_remaining)
					{
						rise_value = money_remaining;
					}
			rise1 = rise_value - call_val;			
					break;
				}
				
			}
		}
		break;
		
		case 8:
		{
			for(i=0;i<14;i++)
			{
				
				temp1 = onepair[i][0];
				temp2 = onepair[i][1];
			
				if(temp1 <= comb_no && temp2 >= comb_no)
				{
					
					last_decision = onepair[i][2];
					rise_decision = onepair[i][3];
					rise_value = onepair[i][4];
					
					if(rise_decision1 == 1)
					{
						last_decision = rise_decision;
					}
					
					if(rise_decision == 1 || last_decision == 1)
					{
						if(call_val<abc[8])
						last_decision = 1;
						else
						last_decision = 0;
					}
					
					if(rise_value<call_val || rise_value<pre_rise_val)
					{
						rise_value = call_val+rise_value;	
					}
				
					if(rise_value>money_remaining)
					{
						rise_value = money_remaining;
					}
			rise1 = rise_value - call_val;			
					break;
				}
				
			}
		}
		break;
		
		case 9:
		{
			for(i=0;i<14;i++)
			{
				
				temp1 = highcard[i][0];
				temp2 = highcard[i][1];
			
				if(temp1 <= comb_no && temp2 >= comb_no)
				{
					
					last_decision = highcard[i][2];
					rise_decision = highcard[i][3];
					rise_value = highcard[i][4];
					
					if(rise_decision1 == 1)
					{
						last_decision = rise_decision;
					}
					rise1 = rise_value - call_val;
					break;
				}
				
			}
		}
		break;
	}
}

void my_decision(int final_decision, int rise_value,int call_value)
{
	
	FILE *help;
	FILE *out;
	out = fopen("outputf.txt","w");

	switch(final_decision)
	{
		case 0:
//		printf("\nFold");
		fprintf(out,"-10");
		break;
		
		case 1:
//		printf("\nCall %d",call_value);
		fprintf(out,"0");
		break;
		
		case 2:
//		printf("Rise %d",rise_value);
		fprintf(out,"%d",rise_value-call_val);
		break;
	}
}

void show_down()
{
	FILE *q,*q1,*q2,*q3;
	
	FILE *open;
	open  = fopen("outputf.txt","w");
	q = fopen("help410.txt","w");
	q1 = fopen("help411.txt","w");
	q2 = fopen("help412.txt","w");
	q3 = fopen("help413.txt","w");
	fprintf(q,"0");
	fprintf(q1,"0");
	fprintf(q2,"0");
	fprintf(q3,"0");
	
	
	fprintf(open,"%d\t%d",hole_card1,hole_card2);
	fclose(open);
}