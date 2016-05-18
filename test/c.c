#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ListSize 500

int f=0;               //用于为无法识别的字符计数
char errorChar[100];  //用于存放暂时无法识别的字符

typedef struct 
{
	char *elem;
	int length;
	int listSize;
}sqList;

typedef struct keyWord
{
	char key[20];
	int number;
    struct keyWord *next;
}keyWord,*keyList;

void InitList(sqList *s);                        //初始化用于存放待分析的程序代码的顺序表
void getList(sqList *s);                        //建立顺序表，暂时存进输入的程序代码
void createKeyWordList(keyList k);             //建立单链表，存放关键字
int AnalysisDemo(sqList *s,keyList k,int i);  //分析程序代码，生成token串输出

//主函数
void main()
{
	sqList s;
	keyList k;
	int i=0;
	k=(keyList)malloc(sizeof(keyWord));
	k->next=NULL;
	printf("输入以 空格+Tab+ \\n 结束\n");
	printf("----------------------------\n");
	createKeyWordList(k);
	InitList(&s);
	getList(&s);
	printf("------------------Token----------------\n\n");
	i=AnalysisDemo(&s,k,0);
	printf("------------------Error----------------\n\n");
	printf("无法分析的字符串：");
	for(i=0;i<f;i++)
	{
		if(errorChar[i]=='\n'||errorChar[i]==32)
		{
			continue;
		}
		else
		{
			printf("%c ",errorChar[i]);
		}
	}
    getch();
}

//初始化用于存放待分析的程序代码的顺序表
void InitList(sqList *s)
{
	s->elem=(char*) malloc(ListSize*sizeof(char));
	s->length=0;
	s->listSize=ListSize;
}
//建立顺序表，暂时存进输入的程序代码
void getList(sqList *s)
{
	int i=0;
	char e;
	scanf("%c",&e);
	while(e!='\t')   //\t为结束
	{
		s->elem[i]=e;
		s->length++;
		i++;
		scanf("%c",&e);
	}
}
//建立单链表，存放关键字
void createKeyWordList(keyList k)
{
	keyList q,p;
	int i;
	q=k;
	for(i=1;i<=35;i++)
	{
		p=(keyList) malloc(sizeof(keyWord));
		p->next=NULL;
		switch(i)
		{
		case 1:    strcpy(p->key,"include");   break;
		case 2:    strcpy(p->key,"void");      break;
		case 3:    strcpy(p->key,"main");      break;
		case 4:    strcpy(p->key,"define");    break;
		case 5:    strcpy(p->key,"int");       break;
		case 6:    strcpy(p->key,"float");     break;
		case 7:    strcpy(p->key,"typedef");   break;
		case 8:    strcpy(p->key,"for");       break;
		case 9:    strcpy(p->key,"while");     break;
		case 10:    strcpy(p->key,"do");       break;
		case 11:    strcpy(p->key,"switch");   break;
		case 12:    strcpy(p->key,"struct");   break;
		case 13:    strcpy(p->key,"sizeof");   break;
		case 14:    strcpy(p->key,"if");       break;
		case 15:    strcpy(p->key,"else");     break;
		case 16:    strcpy(p->key,"return");   break;
		case 17:    strcpy(p->key,"char");     break;
		case 18:    strcpy(p->key,"scanf");    break;
		case 19:    strcpy(p->key,"printf");   break;
		case 20:    strcpy(p->key,"break");    break;
		case 21:    strcpy(p->key,"continue"); break;
		case 22:    strcpy(p->key,"default");  break;
		case 23:    strcpy(p->key,"case");     break;
        case 24:    strcpy(p->key,"const");    break;
		case 25:    strcpy(p->key,"double");   break;
		case 26:    strcpy(p->key,"enum");     break;
		case 27:    strcpy(p->key,"extern");   break;
		case 28:    strcpy(p->key,"goto");     break;
		case 29:    strcpy(p->key,"long");     break;
		case 30:    strcpy(p->key,"short");    break;
		case 31:    strcpy(p->key,"signed");   break;
		case 32:    strcpy(p->key,"unsigned"); break;
		case 33:    strcpy(p->key,"union");    break;
		case 34:    strcpy(p->key,"volatile"); break;
		case 35:    strcpy(p->key,"auto");     break;
		default:                               break;
		}
		p->number=i;
		q->next=p;
		q=q->next;
	}
}
//分析程序代码，生成token串输出
int AnalysisDemo(sqList *s,keyList k,int i)
{
	char a[20];
	int j=0;
	keyList t=k->next;
	if(i<s->length)
	{
		if('a'<=s->elem[i]&&s->elem[i]<='z' || 'A'<=s->elem[i]&&s->elem[i]<='Z' || s->elem[i]=='_')
		{
			while(i<s->length)
			{
				if('a'<=s->elem[i] && s->elem[i]<='z' || 'A'<=s->elem[i] && s->elem[i]<='Z' || s->elem[i]=='_' || '0'<=s->elem[i] && s->elem[i]<='9')
				{
					a[j]=s->elem[i];
					i++;
					j++;
				}
				else
				{
					a[j]='\0';   break;
				}
			}
		}
		else if('0'<=s->elem[i] && s->elem[i]<='9')
		{
			while(i<s->length)
			{
				if('0'<=s->elem[i] && s->elem[i]<='9')
				{
					a[j]=s->elem[i];
					i++;
					j++;
				}
				else
				{
					a[j]='\0';   break;
				}
			}
		}
	}
	if(j>0)
	{
		while(t!=NULL)
		{
			if(strcmp(a,t->key)==0)
			{
				printf("%-20s  %d\n",a,t->number);
				break;
			}
			else
			{
				t=t->next;
			}
			if(t==NULL)
			{
				if('0'<=a[0]&&a[0]<='9')
					printf("%-20s  36\n",a);
				else
					printf("%-20s  37\n",a);
			}
		}
	}
	else if(i<s->length)
	{
		switch(s->elem[i])
		{
		case '(':
			printf("%-20c  41\n",s->elem[i]);
			i++;     break;
		case ')':
			printf("%-20c  42\n",s->elem[i]);
			i++;     break;
		case '[':
			printf("%-20c  43\n",s->elem[i]);
			i++;     break;
		case ']':
			printf("%-20c  44\n",s->elem[i]);
			i++;     break;
		case '.':
			printf("%-20c  45\n",s->elem[i]);
			i++;     break;
		case '%':
			printf("%-20c  46\n",s->elem[i]);
			i++;     break;
		case ',':
			printf("%-20c  47\n",s->elem[i]);
			i++;     break;
		case ';':
			printf("%-20c  48\n",s->elem[i]);
			i++;     break;
		case '#':
			printf("%-20c  49\n",s->elem[i]);
			i++;     break;
		case '\'':
			printf("%-20c  50\n",s->elem[i]);
			i++;     break;
		case '{':
			printf("%-20c  51\n",s->elem[i]);
			i++;     break;
		case '}':
			printf("%-20c  52\n",s->elem[i]);
			i++;     break;
		case '"':
			printf("%-20c  53\n",s->elem[i]);
			i++;     break;
		case ':':
			printf("%-20c  54\n",s->elem[i]);
			i++;     break;
		case '!':
			if(s->elem[i+1]=='=')
			{
				printf("%c%-20c  55\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  56\n",s->elem[i]);
				i++;   break;
			}
		case '+':
			if(s->elem[i+1]=='+')
			{
				printf("%c%-20c  57\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else if(s->elem[i+1]=='=')
			{
				printf("%c%-20c  58\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  59\n",s->elem[i]);
				i++;  break;
			}
		case '-':
			if(s->elem[i+1]=='-')
			{
				printf("%c%-20c  60\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else if(s->elem[i+1]=='=')
			{
				printf("%c%-20c  61\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  62\n",s->elem[i]);
				i++;  break;
			}
		case '*':
			if(s->elem[i+1]=='/')
			{
				printf("%c%-20c  63\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else if(s->elem[i+1]=='=')
			{
				printf("%c%-20c  64\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  65\n",s->elem[i]);
				i++;  break;
			}
		case '/':
			if(s->elem[i+1]=='*')
			{
				printf("%c%-20c  66\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else if(s->elem[i+1]=='=')
			{
				printf("%c%-20c  67\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  68\n",s->elem[i]);
				i++;  break;
			}
		case '>':
			if(s->elem[i+1]=='=')
			{
				printf("%c%-20c  69\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  70\n",s->elem[i]);
				i++;  break;
			}
		case '<':
			if(s->elem[i+1]=='=')
			{
				printf("%c%-20c  71\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  72\n",s->elem[i]);
				i++;  break;
			}
		case '=':
			if(s->elem[i+1]=='=')
			{
				printf("%c%-20c  73\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  74\n",s->elem[i]);
				i++;  break;
			}
		case '&':
			if(s->elem[i+1]=='&')
			{
				printf("%c%-20c  75\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  76\n",s->elem[i]);
				i++;  break;
			}
		case '|':
			if(s->elem[i+1]=='|')
			{
				printf("%c%-20c  77\n",s->elem[i],s->elem[i+1]);
			    i++;  i++;  break;
			}
			else
			{
				printf("%-20c  78\n",s->elem[i]);
				i++;  break;
			}
		default:
			errorChar[f]=s->elem[i];
			f++;  i++;  break;
		}
	}
	if(i>=s->length)
		return 1;
	else
		return AnalysisDemo(s,k,i);
}