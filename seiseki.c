#include<stdio.h>
int main(){
	int a,;
	char ;
	void first(),new(),con();
	first(a);
	if(a==1)new()
	else if(a==2)con();
	else printf("illegal");	
}

void first(int h){
	int h;
	printf("1:初期/n");
	printf("2:継続/n");
	printf("選択:");
	scanf("%d",&h);
}

void new(){
	FILE *fi;
	char c,kamo;
	int i,kamono,people;
	printf("「年度-学年-クラス」を英数字で入力:");
	scanf("%s",c);
	fi=fopen("%s.txt",c"w");
	i=1;kamono=1;people=1;
	while(i==1){
		printf("%dつめの科目:",kamono);
		scanf("%s",kamo);
		fprintf("%s/n",kamo);
		while(){
			printf("%d人目の%s成績入力")
		}
	}
}

