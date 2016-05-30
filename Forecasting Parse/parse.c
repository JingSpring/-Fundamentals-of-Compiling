#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxSize 50

typedef struct 
{
	char statusData[MaxSize];              //状态栈
	int top;
}StatusStack;

int i,now=0;
char e,stringData[MaxSize];        //保存输入的字符串

//$代表：Vo ,G代表 E',H代表 T'

//二维预测分析表:[非终结符，终结符]
char *parse[][6]={
	"TG"," "," ","TG"," "," ",
	" ","+TG"," "," ","$","$",
	"FH"," "," ","FH"," "," ",
	" ","$","*FH","","$","$",
	"i"," "," ","(E)"," "," ",
};                 

void InitStack(StatusStack *s);               //初始化状态栈
char pushStack(StatusStack *s,char e);       //入栈
char popStack(StatusStack *s);              //出栈
char getTop(StatusStack *s);               //获取栈顶元素
void getExpression(char str[]);           //输入缓存区
void displayStack(StatusStack *s);       //显示栈元素
void displayString();                   //显示输入字符串
void forecastingParse();               //预测分析
int rowMatch();                       //行匹配
int columnMatch();                   //列匹配
void rule(char a,char b);           //规则
void match(StatusStack *s);        //匹配

int main()
{
	char c[] = {" "};
	int x,y,b,step,n;       //step:步骤
	char X,a,str[5];       //
	StatusStack s;
	step=0;
	InitStack(&s);    //初始化栈
	pushStack(&s,'#');
	pushStack(&s,'E');
	getExpression(stringData);  //输入字符串
	printf("\n步骤\t\t分析栈\t\t剩余输入串\t\t推导所用产生式或匹配\n");
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
	printf("接受\n");
	goto out;
error1:
	printf("\n出错！！！\n");
	goto out;
out:
	return 0;
}
//初始化状态栈
void InitStack(StatusStack *s)
{
	s->top=0;
}
//入栈
char pushStack(StatusStack *s,char e)
{
	if(s->top==MaxSize)
	{
		printf("栈已满！！！\n");
		return 0;
	}
	s->statusData[s->top]=e;
	s->top++;
	return 1;
}
//出栈
char popStack(StatusStack *s)
{
	i=s->top;
	e=s->statusData[i-1];
	if(s->top==0)
	{
		printf("栈为空！！！\n");
		return 0;
	}
	s->top--;
	return 1;
}
//获取栈顶元素
char getTop(StatusStack *s)
{
	char x;
	i=s->top;
	if(s->top==0)
	{
		printf("栈为空！！！\n");
		//return 0;
	}
	i--;
	x=s->statusData[i];
	return x;
}
//输入缓存区
void getExpression(char str[])
{
	int Length;
	while(1)
	{
		printf("请输入字符串(以'#'结束)：");
		fflush(stdin);
		gets(str);
		Length=strlen(str);
		if(str[Length-1]!='#')
		{
			printf("字符串必须以#号结束，请重新输入!!!\n");
			continue;
		}
		break;
	}
	return;
}
//显示栈元素
void displayStack(StatusStack *s)
{
	if(s->top==0)
	{
		printf("\t栈为空！！！\n");
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
//行匹配
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
//列匹配
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
//规则
void rule(char a,char b)
{
	int x,y;
	x=columnMatch(a);
	y=rowMatch(b);
	printf("%c -> %s",a,parse[x][y]);
}
//匹配
void match(StatusStack *s)
{
	char ch;
	ch = getTop(s);
	printf("%c 匹配",ch);
	popStack(s);
}
//预测分析
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