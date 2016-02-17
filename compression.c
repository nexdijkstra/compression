#include<stdio.h>

int main(int argc, char *argv[])
{
				FILE *read;//압축할 파일 
				FILE *write;//저장할 파일
				int bin=0;
				int zero_cnt=0;//0의 개수를 세는 변수
				int zero_flag=0;//zero가 나왔는지 확인
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
								if(zero_cnt==255)
								{
												fputc(255,write);
												zero_flag=0;
												zero_cnt=0;
								}
								/*파일의 내용이 0 이고 zero_flag가 0이면 (zero가 처음 나오면)*/
									if(bin==0&&zero_flag==0)
								{
												fputc(bin,write);
												zero_flag++;
												continue;
								}else if (bin==0&&zero_flag!=0){//zero가 여러번 나오면 zero_cnt를 증가시키며 0의 갯수를 늘린다
												if(zero_cnt<255)
												{
																zero_cnt++;
												}
												continue;				
								}else if(bin!=0)//파일의 내용이 0이 아니면
								{
												if(zero_flag!=0){//zero가 여러번 나왔었더라면 0x(x는 zero의 갯수)
																fputc(zero_cnt,write);
																fputc(bin,write);
																zero_cnt=0;
																zero_flag=0;
												}else//그냥 복사한다.
												{
																fputc(bin,write);
																zero_cnt=0;
																zero_flag=0;
												}
												continue;
								}
				}
				fclose(read);
				fclose(write);

}
