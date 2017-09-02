# include<stdio.h>
# include<stdlib.h>
# include<ctype.h>
#define INIT_SIZE 50
#define MAXBUFFER 10
#define INCREMENT 10

typedef double ElemType;
typedef struct stack
{
	ElemType *top;
	ElemType *base;
	int stacksize;
}stack;

void Init(stack * s)
{
	s->base=(ElemType *)malloc(sizeof(ElemType)*INIT_SIZE);

	s->top=s->base;

	s->stacksize=INIT_SIZE-1;

	return;
}

void Pop(stack *s,ElemType* e)
{
	if(s->top==s->base)
		return;
		
	*e=*--(s->top);
		return ;
}

void Push (stack *s, ElemType e)
{
	if(s->top - s->base >=s->stacksize)
	{
		s->base=(ElemType*)realloc(s->base,sizeof(ElemType)*(s->stacksize+1+INCREMENT));
		s->top =s->base + s->stacksize;
		s->stacksize=s->stacksize+INCREMENT;
	}
		*(s->top)=e;
		s->top++;

		return;
}

int isempty(stack s)
{
	if(s.top == s.base)
		return 1;
	else
		return 0;
}

int main (void)
{
	stack s;
	stack RPN;
	char c;
	ElemType e,d;
	Init(&s);
	Init(&RPN);
	char String[100];
	char str[MAXBUFFER];
	int i=0 ,j=0;
	

	printf("Ingresa el cálculo (Suma, Resta, multiplicación y División. Pueden usarse paréntesis).\nPresiona Enter para finalizar\nEjemplo= 5*(6+2.5)+(3-3/2)/6\n");
	scanf("%c",&c);
	// 10 in ascii is new line
	while(c!=10)
	{
		while((c >='0' && c <='9')|| c=='.' )
		{
			String[i++]=c;
			scanf("%c",&c);

			if((c<'0' || c>'9')&& c!='.')
				String[i++]=' ';
		}
	
		//if there is right parenthesis, pop everything out of the stack until there is left parenthesis
		if (c==')')
		{
			Pop(&s,&e);
			while(e!='(')
			{
				String[i++]=e;
				String[i++]=' ';
				Pop(&s,&e);
			}
		}
		else if( c =='+' || c=='-')
		{
			if( isempty(s))
				Push(&s,c);
			else {
				do
				{
					Pop(&s,&e);
					if('('==e)
					{
						Push(&s,e); //push back, if there is left parethesis
					}
					else
					{
						String[i++]=e;
						String[i++]=' ';
					}
				}while( !isempty(s) && e!='(');
				Push(&s,c);
			}
		}
		else if (c=='(')
			Push(&s,c);
		else if( c== '*' || c=='/')
		{
			if( isempty(s))
				Push(&s,c);
			else
			{
				do
				{	Pop(&s,&e);
					if(e =='+' ||e== '-'|| e=='(')
					{
						Push(&s,e);
					}
					else
					{
						String[i++]=e;
						String[i++]=' ';
					}
				}while( !isempty(s) && e!='('&& e!='+'&& e!='-');
				Push(&s,c);
			}	
		}
		else if (c==10)
			break;
		else if (c==' ');
		else {
		 printf("ERROR: Formato incorrecto %d",c);
			
		}

		scanf("%c",&c);
	}
	while(! isempty(s))
	{
		Pop(&s,&e);
		String[i++]=e;
		String[i++]=' ';
	}
	String[i++]='#';
	String[i]='\0';

	

// above code change infix to post fix. 
	i=0;
	while( (c=String[i++])!='#' )
	{
		while( isdigit(c) || c=='.')
		{
			str[j++]=c;
			str[j]='\0';
			if(j>MAXBUFFER-1)
			{
				printf("ERROR: Número demasido grande\n");
				return 0;
			}
			c=String[i++];
			if(c ==' ')
			{
				d=atof(str);
				Push(&RPN,d);
				j=0;
			}
		}
		
		switch(c)
		{
		case '+':
			Pop(&RPN,&d);
			Pop(&RPN,&e);
			Push(&RPN,d+e);
			break;
		case '-':
			Pop(&RPN,&d);
			Pop(&RPN,&e);
			Push(&RPN,e-d);
			break;
		case '*':
			Pop(&RPN,&d);
			Pop(&RPN,&e);
			Push(&RPN,d*e);
			break;
		case '/':
			Pop(&RPN,&d);
			Pop(&RPN,&e);
			if( d==0)
			{
				printf("ERROR: División por 0\n");
				return 0;
			}
			else
				Push(&RPN,e/d);
			break;
		}
		
	}

	Pop(&RPN,&d);
	printf("\n%lf\n",d);

return 0;
}