#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxSize 50

typedef struct 
{
	char statusData[MaxSize];              //״̬ջ
	int top;
}StatusStack;

int i,now=0;
char e,stringData[MaxSize];        //����������ַ���

//$����Vo ,G���� E',H���� T'

//��άԤ�������:[���ս�����ս��]
char *parse[][6]={
	"TG"," "," ","TG"," "," ",
	" ","+TG"," "," ","$","$",
	"FH"," "," ","FH"," "," ",
	" ","$","*FH","","$","$",
	"i"," "," ","(E)"," "," ",
};                 

void InitStack(StatusStack *s);               //��ʼ��״̬ջ
char pushStack(StatusStack *s,char e);       //��ջ
char popStack(StatusStack *s);              //��ջ
char getTop(StatusStack *s);               //��ȡջ��Ԫ��
void getExpression(char str[]);           //���뻺����
void displayStack(StatusStack *s);       //��ʾջԪ��
void displayString();                   //��ʾ�����ַ���
void forecastingParse();               //Ԥ�����
int rowMatch();                       //��ƥ��
int columnMatch();                   //��ƥ��
void rule(char a,char b);           //����
void match(StatusStack *s);        //ƥ��

int main()
{
	char c[] = {" "};
	int x,y,b,step,n;       //step:����
	char X,a,str[5];       //
	StatusStack s;
	step=0;
	InitStack(&s);    //��ʼ��ջ
	pushStack(&s,'#');
	pushStack(&s,'E');
	getExpression(stringData);  //�����ַ���
	printf("\n����\t\t����ջ\t\tʣ�����봮\t\t�Ƶ����ò���ʽ��ƥ��\n");
one:
	X=getTop(&s);
	a=stringData[now];
	b=rowMatch(X);
	if(b==0 || b==1 || b==2 || b==3 || b==4)
		goto two;
	else
		goto three;
two:
	if(X==a)
	{
		step++;
		printf("%d\t\t",step);
		displayStack(&s);
		putchar('\t');
		putchar('\t');
		displayString();
		putchar('\t');
		putchar('\t');
		putchar('\t');
		forecastingParse(&s);
		putchar(10);
		now++;
		goto one;
	}
	else
	{
		goto error1;   //
	}
three:
	if(X=='#')
	{
		if(X!=a)
			goto error1;
		else
			goto five;
	}
	else
		goto fou;
fou:
	x=columnMatch(X);
	y=rowMatch(a);
	if(strcmp(parse[x][y],c)==0)
		goto error1;
	else
	{
		step++;
		printf("%d\t\t",step);
		displayStack(&s);
		putchar('\t');
		putchar('\t');
		displayString();
		putchar('\t');
		putchar('\t');
		putchar('\t');
		forecastingParse(&s);
		putchar(10);
		strcpy(str,parse[x][y]);
		popStack(&s);
		for(n=strlen(str);n>0;n--)
		{
			pushStack(&s,str[n-1]);
			if(getTop(&s)=='$')
			{
				popStack(&s);
			}
		}
		goto one;
	}
five:
	step++;
	printf("%d\t\t",step);
	displayStack(&s);
	putchar('\t');
	putchar('\t');
	displayString();
	putchar('\t');
	putchar('\t');
	putchar('\t');
	printf("����\n");
	goto out;
error1:
	printf("\n��������\n");
	goto out;
out:
	return 0;
}
//��ʼ��״̬ջ
void InitStack(StatusStack *s)
{
	s->top=0;
}
//��ջ
char pushStack(StatusStack *s,char e)
{
	if(s->top==MaxSize)
	{
		printf("ջ����������\n");
		return 0;
	}
	s->statusData[s->top]=e;
	s->top++;
	return 1;
}
//��ջ
char popStack(StatusStack *s)
{
	i=s->top;
	e=s->statusData[i-1];
	if(s->top==0)
	{
		printf("ջΪ�գ�����\n");
		return 0;
	}
	s->top--;
	return 1;
}
//��ȡջ��Ԫ��
char getTop(StatusStack *s)
{
	char x;
	i=s->top;
	if(s->top==0)
	{
		printf("ջΪ�գ�����\n");
		//return 0;
	}
	i--;
	x=s->statusData[i];
	return x;
}
//���뻺����
void getExpression(char str[])
{
	int Length;
	while(1)
	{
		printf("�������ַ���(��'#'����)��");
		fflush(stdin);
		gets(str);
		Length=strlen(str);
		if(str[Length-1]!='#')
		{
			printf("�ַ���������#�Ž���������������!!!\n");
			continue;
		}
		break;
	}
	return;
}
//��ʾջԪ��
void displayStack(StatusStack *s)
{
	if(s->top==0)
	{
		printf("\tջΪ�գ�����\n");
	}
	else
	{
		for(i=0;i<s->top;i++)
		{
			printf("%c",s->statusData[i]);
		}
	}
}
void displayString()
{
	int j;
	for(j=now;;)
	{
		printf("%c",stringData[j]);
		j++;
		if(stringData[j]=='\0')
		{
			break;
		}
	}
}
//��ƥ��
int rowMatch(char x)
{
	switch(x)
	{
	case 'i':return 0; break;
	case '+':return 1; break;
	case '*':return 2; break;
	case '(':return 3; break;
	case ')':return 4; break;
	case '#':return 5; break;
	default:return -1;
	}
}
//��ƥ��
int columnMatch(char x)
{
	switch(x)
	{
	case 'E':return 0; break;
	case 'G':return 1; break;
	case 'T':return 2; break;
	case 'H':return 3; break;
	case 'F':return 4; break;
	default:return -1;
	}
}
//����
void rule(char a,char b)
{
	int x,y;
	x=columnMatch(a);
	y=rowMatch(b);
	printf("%c -> %s",a,parse[x][y]);
}
//ƥ��
void match(StatusStack *s)
{
	char ch;
	ch = getTop(s);
	printf("%c ƥ��",ch);
	popStack(s);
}
//Ԥ�����
void forecastingParse(StatusStack *s)
{
	char k,*p;
	k=getTop(s);
	p=&stringData[now];
	if(*p==k)
		match(s);
	else
		rule(k,*p);
}