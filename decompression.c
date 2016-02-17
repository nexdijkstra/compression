#include<stdio.h>

int main(int argc, char *argv[])
{
				FILE *read;//압출풀 파일
				FILE *write;//압축 해제한 파일
				char filename[511];
				int bin=0;
				int zero_cnt=0;
				int zero_flag=0;
				if((read=fopen(argv[1],"rb"))==NULL)
				{
								printf("read file open error\n");
								return 0;
				}
				if((write=fopen(argv[2],"wb"))==NULL)
				{
								printf("write file open error\n");
								return 0;
				}

				while((bin=fgetc(read))!=EOF)
				{
								if(zero_flag!=0)//0다음 숫자는 0의 갯수
								{
												zero_cnt=bin;
												while(zero_cnt!=0)//0의 개수만큼 0을 쓴다
												{
																putc(0,write);
																zero_cnt--;
												}
												zero_cnt=0;
												zero_flag=0;
												continue;
								}

								if(bin==0&&zero_flag==0)//0이 처음 나오면 0을 써주고 zero_flag를 증가
								{
												fputc(bin,write);
												zero_flag++;
												continue;

								}else if(bin!=0)//0이 아니면 복사
								{
												fputc(bin,write);
												zero_cnt=0;
												zero_flag=0;
												continue;
								}
				}
        sprintf(filename,"chmod 775 %s",argv[2]);
				system(filename);				
				fclose(read);
				fclose(write);
				return 0;
}
