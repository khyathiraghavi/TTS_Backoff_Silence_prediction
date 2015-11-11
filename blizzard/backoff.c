#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 100000000
#define MAX2 10000
#define OVERLAP 25

int check1 (char * syl, int found);
int check2 (char * syl, int found);
int checkAvailable (char * c, char ** arr, int num);
//void concatenate();
char * dequeue ();
void enqueue( char * str);
void empty (char *, int);
void removeSubstring(char *s,const char *toremove);
void insert_substring(char *a, char *b, int position);
char *substring(char *string, int position, int length);
int break_syllable(char * syllable, char, int found);
int break_down(char * syllable, char, int found);


typedef struct queue
{
	int in;
	int out;
	char ** s;
}queue;

queue Q;
char ** syllables;
int num_syl=0;


int main(int argc, char * argv[])
{
	int BUFSIZE,i,count=0,pos=0, found=0, dec=0,flag,j,prev,l,epos_i=0,len,flag1,cluster,epos[10];
	int vow_i=0, sym_i=0, quant_i=0, phone_i=0,cnst_i=0;
	short int * final;
	char * syl, * syl_cpy, * input, * temp,**phoneset, **vow, **sym, **cnst, **quantifier, st[10], phn[10], quant[10], temp1, temp2, temp3, * temp4, *str, temp5[30], temp6[30], temp7[30], v;
	temp=(char *)malloc(sizeof(char)*1000);
	temp4=(char *)malloc(sizeof(char)*1000);
	//strcpy(temp,argv[1]);
	//FILE * inp_file=fopen(temp,'r');
	FILE * inp_file, * syl_file;
	FILE * lang_file;
	inp_file=fopen(argv[1],"r");
	syl_file=fopen(argv[2],"r");
	lang_file  = fopen(argv[3],"r");
	FILE * wav_file;
	FILE * out_file = fopen(argv[4],"w");
	syllables = (char **)malloc(sizeof(char*)*MAX2);
	quantifier = (char **)malloc(sizeof(char*)*MAX2);
	phoneset = (char **)malloc(sizeof(char*)*MAX2);
	vow = (char **)malloc(sizeof(char*)*MAX);
	sym = (char **)malloc(sizeof(char*)*MAX);
	cnst = (char **)malloc(sizeof(char*)*MAX);
	Q.in=0;
	Q.out=-1;
	Q.s = (char **)malloc(sizeof(char*)*MAX2);
	for(i=0;i<MAX2;i++)
	{
		*(syllables+i)=(char *)malloc(sizeof(char)*10);	
		*(quantifier+i)=(char *)malloc(sizeof(char)*6);	
		*(phoneset+i)=(char *)malloc(sizeof(char)*6);	
		*(vow+i)=(char *)malloc(sizeof(char)*6);	
		*(sym+i)=(char *)malloc(sizeof(char)*6);
		*(cnst+i)=(char *)malloc(sizeof(char)*6);
		*(Q.s+i)=(char *)malloc(sizeof(char)*10);
	}
	syl = (char *)malloc(sizeof(char)*50);
	syl_cpy = (char *)malloc(sizeof(char)*50);
	input = (char *)malloc(sizeof(char)*50);
	final=(short *)malloc(sizeof(float)*MAX);
	//reading phoneset of the language
	while(fscanf(lang_file,"%[^\t]%c%[^\n]%c",phn,&temp2,quant,&temp3)!=EOF)
	{
		if(checkAvailable(phn,phoneset,phone_i)<0)
		{
			strcpy(*(phoneset+phone_i++),phn);			
			strcpy(*(quantifier+quant_i++),quant);
			if(strcmp(quant,"VOW")==0)
				strcpy(*(vow+vow_i++),phn);
			if(strcmp(quant,"SYM")==0)
				strcpy(*(sym+sym_i++),phn);
			if(strcmp(quant,"CON")==0)
				strcpy(*(cnst+cnst_i++),phn);

		}	
	}
	//reading syllables in the language
	while(fscanf(syl_file,"%s",syl)!=EOF)
	{
		strcpy(*(syllables+num_syl++),syl);
	}

//	printf("here\n");
	while(fscanf(inp_file,"%s",syl)!=EOF)
	{
//		printf("after scan: %s\n",syl);
		strcpy(syl_cpy,syl);
		if(strcmp(syl,"SIL")==0)
		{
			enqueue(syl);
			continue;
		}
		printf("%s\t",syl);
		found=0;
//		printf("check1:::\n");
		found=check1(syl,found);
//		printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%s\n",syl);
//		if(found==0)
//			printf("passed\n");
		if(found==0)
		{
//			printf("check2:::\n");
			found=check2(syl,found);
//			if(found==0)
//				printf("passed\n");
		}
//		printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%s\n",syl);
		/*if(found==0)
		{
			flag=1;
			dec=1;
			strncpy(temp,syl,strlen(syl)-2);
//			printf("***%s %s\n",temp,syl);
			while(checkAvailable(temp+strlen(temp)-dec,vow,vow_i)<0)
			{
A:				dec++;
//				printf("%d\n",dec);
				if(dec>=strlen(temp)-1)
				{
					flag=0;
					break;
				}
			}
			if(flag==1)
			{
				strncpy(temp4,temp,strlen(temp)-dec);
				strcat(temp4,"_s");
				found=check1(temp4,found);
				if(found==0)
					found=check2(temp4,found);
//				if(found==1)
//					printf("passed\n");
				if(found==0 && dec<strlen(temp))
					goto A;
				if(found==1)
				{
					strcpy(temp4,temp+strlen(temp)-dec);
					strcat(temp4,"_m");
					enqueue(temp4);
				}
			}
			if(found==1)
				printf("check3::: %s\n",syl);

		}*/
//		printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%s\n",syl);
		if(found==0)
		{
			cluster=0;
			epos_i=0;
			prev=-1;
			flag=-1;
			empty(temp,1000);
			strncpy(temp,syl,strlen(syl)-2);
			l=strlen(temp);
			dec=0;
			while(dec<l)	
			{
				printf("here\n");
				strncpy(temp7,temp+dec,4);
				temp7[4]='\0';
				strncpy(temp4,temp+dec,3);
				temp4[3]='\0';
				strncpy(temp5,temp+dec,2);
				temp5[2]='\0';
				strncpy(temp6,temp+dec,1);
				temp6[1]='\0';
				printf("temp7: %s temp4: %s temp5: %s temp6:%s\n",temp7,temp4,temp5,temp6);
				flag=0;
				if(checkAvailable(temp7,cnst,cnst_i)>=0)
				{
					printf("c7\n");
					flag=1;
					dec+=4;
					len=4;
				}
				else if(checkAvailable(temp4,cnst,cnst_i)>=0)
				{
					printf("c4\n");
					flag=1;
					dec+=3;
					len=3;
				}
				else if(checkAvailable(temp5,cnst,cnst_i)>=0)
				{
					printf("c5\n");
					flag=1;
					dec+=2;
					len=2;
				}
				else if(checkAvailable(temp6,cnst,cnst_i)>=0)
				{
					printf("c6\n");
					flag=1;
					dec+=1;
					len=1;
				}
				else if(checkAvailable(temp7,vow,vow_i)>=0)
				{
					printf("v7\n");
					flag=2;
					dec+=4;
					len=4;
				}
				else if(checkAvailable(temp4,vow,vow_i)>=0)
				{
					printf("v4\n");
					flag=2;
					dec+=3;
					len=3;
				}
				else if(checkAvailable(temp5,vow,vow_i)>=0)
				{
					printf("v5\n");
					flag=2;
					dec+=2;
					len=2;
				}
				else if(checkAvailable(temp6,vow,vow_i)>=0)
				{
					printf("v6\n");
					flag=2;
					dec+=1;
					len=1;
				}
				else
					dec++;
				if(flag==1 && prev==1)
				{
//					printf("cluster %d\n",dec);
					epos[epos_i++]=dec-len;
					//printf("%c %d %d %d\n",*(syl+strlen(syl)-1),dec,l-1,epos);
					if((dec>(l-1)) && (*(syl+strlen(syl)-1)=='l' || *(syl+strlen(syl)-1)=='w'))
					{
						if(strcmp(temp6,"c")==0 || strcmp(temp5,"ch")==0 || strcmp(temp6,"j")==0 || strcmp(temp5,"jh")==0 || strcmp(temp5,"ng")==0)
						{
							insert_substring(syl,"i",epos[epos_i--]+1);
							//insert_substring(syl,"i",dec-1+len);
							v='i';
						}
						else
						{
							printf("%d\n",epos[epos_i--]+1);
							printf("till here\n");
							insert_substring(syl,"u",epos[epos_i--]+1);
							//insert_substring(syl,"u",dec+1-len);
							v='u';
						//printf("syl: %s\n",syl);
						}
						//epos=-1;
					}
					flag1=1;
					cluster=1;
				}
				printf("flag:%d prev:%d epos:%d\n",flag,prev,epos_i);
				if(flag==2 && prev==1 && epos_i!=-1)
				{
					while(epos_i>0)
					{
						printf("vowel daggara insertion %s %d %d\n",temp6,dec,len);
						if(len==1)
						{
							insert_substring(syl,temp6,epos[--epos_i]+1);
						}
						else if(len==2)
						{
							printf("breaking clusters\n");
							insert_substring(syl,temp5,epos[--epos_i]+1);
						}
						else if(len==3)
						{
							insert_substring(syl,temp4,epos[--epos_i]+1);
						}
						else if(len==4)
						{
							printf("breaking clusters  4\n");
							insert_substring(syl,temp7,epos[--epos_i]+1);
						}
					}
					//printf("syl2: %s\n",syl);
					//epos=dec;
					flag1=2;
				}
				if(flag!=0)
				{
					len=1;
					prev=flag;
				}
				else
					len++;
			}
			/*if(flag1==1 && epos!=-1)
			{
				if(v=='a')
					insert_substring(syl,"a",epos+1);
				else if(v=='i')
						insert_substring(syl,"i",epos+1);
				else if(v=='u')
					insert_substring(syl,"u",epos+1);
				flag1=0;
				epos=-1;
			}*/
		}
		printf("found: %d\n",found);
		printf("&&&&&&&&&&&(((((((((((((((%s\n",syl);
		if(found==0)
		{
			found=break_syllable(syl,*(syl+strlen(syl)-1),found);
		}
		if(found==0)
		{
			found=break_down(syl,*(syl+strlen(syl)-1),found);
		}
		if(found==0)
		{
			printf("%s : failed",syl_cpy);
		}
		printf("\n");
		//printf("%d\n",meta->subchunk2_size);
		//printf("%d\n",meta_final->subchunk2_size);

	}
	printf("::::::::::::::::queuing done::::::::::::::::::::\n");
	while(Q.out<Q.in-1)
	{
//		printf("%d %d\n",Q.in,Q.out);
		syl=dequeue();
		fprintf(out_file,"%s\n",syl);
	}
	//fwrite(final,1,1000000,out_file);
	if (inp_file) { fclose(inp_file); }
	if (out_file) { fclose(out_file); }

}
int checkAvailable (char * c, char ** arr, int num)
{
	int i;
	for(i=0;i<num;i++)
	{
		if(strcmp(c,*(arr+i))==0)
			return i;
	}
	return -1;
}
int check1 (char * syl, int found)
{
	if(checkAvailable(syl,syllables,num_syl)>=0)
	{
		found=1;
		enqueue(syl);
	}
	return found;	
}
int check2 (char * syl, int found)
{
	char * temp;
	int flag=0;
	temp=(char *)malloc(sizeof(char)*1000);
	strcpy(temp,syl);
	if(*(temp+strlen(temp)-1)=='w' && found==0)
	{
B:		*(temp+strlen(temp)-1)='b';
		found=check1(temp,found);
		flag=1;
	}
	if(*(temp+strlen(temp)-1)=='b' && found==0)
	{
		*(temp+strlen(syl)-1)='m';
		found=check1(temp,found);
	}
	if(*(temp+strlen(temp)-1)=='m' && found==0)
	{
		*(temp+strlen(temp)-1)='l';
		found=check1(temp,found);
	}
	if(found==0)
	{
		*(temp+strlen(temp)-1)='w';
		found=check1(temp,found);
		if(found==0 && flag==0)
			goto B;
	}
	free(temp);
	return found;	
}
int break_syllable(char * syllable, char end, int found)
{
	printf("breaking :: %s\n",syllable);
	found=check1(syllable,found);
	if(found==1)
	{
//		printf("return %d\n",found);
		return 1;
	}
	found=check2(syllable,found);
	if(found==1)
	{
//		printf("return %d\n",found);
		return found;
	}
	char * syl, *temp;
	int i,flag,l;
	syl=(char *)malloc(sizeof(char)*1000);
	temp=(char *)malloc(sizeof(char)*1000);
	strcpy(syl,syllable);
	l=strlen(syl);
	*(syl+l-1)='\0';
	*(syl+l-2)='\0';
	l-=2;
	flag=0;
//	printf("===== syl: %s  %c\n",syl,end);
	for(i=l-1;i>0;i--)
	{
//		printf("------------*%d\n",i);
		empty(temp,1000);
		strncpy(temp,syl,i);
		strcat(temp,"_");
		if(i==l-1)
		{
			if(end=='m')
				strcat(temp,"m");
			if(end=='b')
				strcat(temp,"b");
			if(end=='l')
				strcat(temp,"l");
			if(end=='w')
				strcat(temp,"w");
		}
		else
		{
			if(end=='b')
				strcat(temp,"b");
			else
				strcat(temp,"m");
		}
//		printf("**********temp: %s\n",temp);
		if(/*check1(temp,found)==1 || */check2(temp,found)==1)
		{
//			printf("*******statisfied for %d\n",i);
			empty(temp,1000);
			strcpy(temp,syl+i);
//			printf("**********temp: %s\n",temp);
			strcat(temp,"_");
			if(i==0 && end=='b')
			{
//				printf("_b\n");
				strcat(temp,"b");
			}
			else
			{
				printf("here   here  _%c\n",end);
				if(end=='w' || end=='l')
					strcat(temp,"l");
				else if(end=='b' || end=='m')
					strcat(temp,"m");
				/*if(end=='s')
					strcat(temp,"s");*/
			}
//			printf("****** calling again for: %s\n",temp);
			if(break_syllable(temp,*(temp+strlen(temp)-1),found)==1)
			{
				found=1;
				break;
			}
			else
			{
//				printf("dequeue\n");
				Q.in--;
			}
		}
//		printf("**********temp: %s\n",temp);
	}
	free(syl);
	free(temp);
	return found;	
}
int break_down(char * syllable, char end, int found)
{
	printf("down :: %s\n",syllable);
	found=check1(syllable,found);
	if(found==1)
	{
//		printf("return %d\n",found);
		return 1;
	}
	found=check2(syllable,found);
	if(found==1)
	{
//		printf("return %d\n",found);
		return found;
	}
	char * syl, *temp;
	int i,flag,l;
	syl=(char *)malloc(sizeof(char)*1000);
	temp=(char *)malloc(sizeof(char)*1000);
	strcpy(syl,syllable);
	l=strlen(syl);
	*(syl+l-1)='\0';
	*(syl+l-2)='\0';
	l-=2;
	flag=0;
//	printf("===== syl: %s  %c\n",syl,end);
	for(i=l-1;i>0;i--)
	{
//		printf("------------*%d\n",i);
		empty(temp,1000);
		strncpy(temp,syl,i);
		strcat(temp,"_");
		if(i==l-1)
		{
			if(end=='m')
				strcat(temp,"m");
			if(end=='b')
				strcat(temp,"b");
			if(end=='l')
				strcat(temp,"l");
			if(end=='w')
				strcat(temp,"w");
		}
		else
		{
			if(end=='b')
				strcat(temp,"b");
			else
				strcat(temp,"m");
		}
		printf("**********temp: %s\n",temp);
		if(/*check1(temp,found)==1 || */check2(temp,found)==1)
		{
//			printf("*******statisfied for %d\n",i);
			empty(temp,1000);
			strcpy(temp,syl+i);
//			printf("**********temp: %s\n",temp);
			strcat(temp,"_");
			if(i==0 && end=='b')
			{
//				printf("_b\n");
				strcat(temp,"b");
			}
			else
			{
				printf("here   here  _%c\n",end);
				if(end=='w' || end=='l')
					strcat(temp,"l");
				else if(end=='b' || end=='m')
					strcat(temp,"m");
				/*if(end=='s')
					strcat(temp,"s");*/
			}
//			printf("****** calling again for: %s\n",temp);
			if(break_down(temp,*(temp+strlen(temp)-1),found)==1)
			{
				found=1;
				break;
			}
			/*else
			{
//				printf("dequeue\n");
				Q.in--;
			}*/
			return;
		}
//		printf("**********temp: %s\n",temp);
	}
	strcat(syllable,"*");
	enqueue(syllable);
	free(syl);
	free(temp);
	return found;	
}
/*void concatenate()
  {
  int i, pos=0;
  char * syl;
  syl = (char *)malloc(sizeof(char)*50);
  while(Q.out<=Q.in)
  {
  syl=dequeue();
  strcpy(input,"samples/");
  strcat(input,syl);
  strcat(input,".wav");
  wav_file=fopen(input,"rb");
  printf("%s\n",syl);
  if(count==0)
  {
//printf("it\n");
fread(meta_final,1,sizeof(header),wav_file);
BUFSIZE = meta_final->chunk_size - 36;
fread(inbuff16, 1, BUFSIZE, wav_file);

for(i=0;i<meta_final->subchunk2_size/2;i++)
{	
 *(final + pos++) = *(inbuff16+i);
 }
 }
 else
 {
 fread(meta,1,sizeof(header),wav_file);
 BUFSIZE = meta->chunk_size - 36;
 fread(inbuff16, 1, BUFSIZE, wav_file);
 meta_final->subchunk2_size+=meta->subchunk2_size;
 pos-=OVERLAP;
 for(i=0;i<meta->subchunk2_size/2;i++)
 {	
 if(i<=OVERLAP)
 {
 *(final+pos)+=*(inbuff16+i);
 *(final+pos)/=2;
 }
 else
 {
 *(final + pos) = *(inbuff16+i);
 }
 pos++;
 }
 }
 }
 }*/
void enqueue(char * str)
{
	strcpy(*(Q.s+Q.in),str);
	Q.in=(Q.in+1)%MAX2;
}
char * dequeue ()
{
	Q.out=(Q.out+1)%MAX2;
	return *(Q.s+Q.out);
}
void empty (char * string, int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		*(string+i)='\0';
	}
}
void removeSubstring(char *s,const char *toremove)
{
	  while( s=strstr(s,toremove) )
		  memmove(s,s+strlen(toremove),1+strlen(s+strlen(toremove)));
}
void insert_substring(char *a, char *b, int position)
{
	printf("position: %d\n",position);
	char *f, *e;
	int length;

	length = strlen(a);
	f = substring(a, 1, position - 1 );      
	printf("debug length: %d position: %d length-position+1: %d\n",length,position,length-position+1);
	e = substring(a, position, length-position+1);

	strcpy(a, "");
	strcat(a, f);
	free(f);
	strcat(a, b);
	strcat(a, e);
	free(e);
	printf("inserted %s\n",a);
}
char *substring(char *string, int position, int length) 
{
	char *pointer;
	int c;

	pointer = malloc(length+1);

	if( pointer == NULL )
		exit(EXIT_FAILURE);

	for( c = 0 ; c < length ; c++ ) 
		*(pointer+c) = *((string+position-1)+c);       

	*(pointer+c) = '\0';

	return pointer;
}
