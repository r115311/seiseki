#include<stdio.h>
#include<stdlib.h>
#include<string.h>
	int stu,sub,i,t,p,u,cho;//p,stu,subは変更しないこと
	float seiseki[50][50]; //0.0は空白、人.科目(それぞれ+1で平均
	char kamokumei[100][100];//科目名.指定なし（0なし
	char seitomei[100][100];//生徒名.指定なし（0なし）
	int juni[50][50];//seisekiの裏側（同一変数指定	
	void check();//確認ができる
	void first();//データ入力
	void rank();//順位計算
	void ave();//平均点算出後rank();
	void save();//データ保存
	void read();//データ読み込み後continuation();
	void continuation();//ロード動作
	void add();//データ追加動作後ave();save();
	void change();//データ書き換え後ave();save();
	void figure();//gnuplotを用いた分布表。動作後CONTINUE MENUへ。
int main(){


	
	
	printf("-----MAIN MENU-----\n");
	printf("  1.新規\n");
	printf("  2.ロード\n");
	printf("番号を選択:");
	scanf("%d",&cho);//cho...メインメニュー選択変数
	printf("-------------------\n");
	
	if(cho==1){
		first();
		ave();
		printf("1.保存\n");
		printf("2.保存しない\n");
		printf("Choose:");
		scanf("%d",&i);
		if(i==1)save();
	}else if(cho==2)read();
	else printf("illeagal");
	
	
	continuation();
	return 0;
}
void first(){
	printf("生徒数を入力：");
	scanf("%d",&stu);
	printf("科目数を入力：");
	scanf("%d",&sub);
	
	p=0;
	for(u=1;u<=stu;++u){
		printf("%d人目の名前を入力:",u);
		scanf("%s",seitomei[u]);
	}
	for(i=1;i<=sub;++i){
		for(t=1;t<=stu;++t){
			if(p==0){
				printf("科目名を入力:");
				scanf("%s",kamokumei[i]);
				p=1;
			}
		printf("%sの%sの点数を入力:",seitomei[t],kamokumei[i]);
		scanf("%f",&seiseki[t][i]);
		if(seiseki[t][i]>100)seiseki[t][i]=100;
		}
		p=0;
	}

}

void check(){
	int no,m,kakukamo;
	printf("確認したい学生の出席番号を入力:");
	scanf("%d",&no);
	for(m=1;m<=sub;m++){
		printf("No.%d %s\n",m,kamokumei[m]);
	}
	printf("%sの確認したい成績の科目番号を入力:",seitomei[no]);
	scanf("%d",&kakukamo);
	printf("%sの%sの成績は%.0f 順位は%d\n",seitomei[no],kamokumei[kakukamo],seiseki[no][kakukamo],juni[no][kakukamo]);
	printf("入力した%sの成績の平均点は%.0f\n",kamokumei[kakukamo],seiseki[stu+1][kakukamo]);
	printf("%sの平均点は%.0f　順位は%d\n",seitomei[no],seiseki[no][sub+1],juni[no][sub+1]);
	
}

void rank(){
	int hito,kamoku,ans,u;
	for(hito=1;hito<=stu;hito++){
		for(kamoku=1;kamoku<=sub+1;kamoku++){
			ans=1;
			for(u=1;u<=stu;u++){
				if(seiseki[hito][kamoku]<seiseki[u][kamoku])ans++;
				juni[hito][kamoku]=ans;
			}
		}
	}//科目内順位(平均点含む
}
void ave(){
	float ans;
	int sum,tate,yoko;
	for(yoko=1;yoko<=sub;yoko++){
		sum=0;
		for(tate=1;tate<=stu;tate++){
			sum+=seiseki[tate][yoko];
		}
		ans=sum/stu;
		seiseki[stu+1][yoko]=ans; //科目の平均点を全生徒下部
	}
	for(tate=1;tate<=stu;tate++){
		sum=0;
		for(yoko=1;yoko<=sub;yoko++){
			sum+=seiseki[tate][yoko];
		}
		ans=sum/sub;
		seiseki[tate][sub+1]=ans;//個人の平均点を生徒右部
	}
	seiseki[stu+1][sub+1]=0;//空白部分の回避
	rank();
	
}

void save(){
	char savename[100];
	printf("「年度-学年-クラス」を入力:");
	scanf("%s",savename);
	
	FILE *fp;
	fp=fopen(savename,"w");
	//各種変数保存
	fprintf(fp,"%d %d\n",stu,sub);//1行目に生徒数.科目数（改行
	//成績、平均点出力
	for(i=1;i<=stu+1;i++){
		for(t=1;t<=sub+1;t++){//それぞれ+1は平均点
			fprintf(fp,"%.0f ",seiseki[i][t]);
		}
		fprintf(fp,"\n");
	}				
	
	//順位出力
	for(i=1;i<=stu;i++){
		for(t=1;t<=sub+1;t++){//平均点順位のため+1
			fprintf(fp,"%d ",juni[i][t]);
		}
		fprintf(fp,"\n");
	}
	
	//科目名出力
	for(i=1;i<=sub;i++){
		fprintf(fp,"%s\n",kamokumei[i]);
	}
	
	//生徒名出力
	for(i=1;i<=stu;i++){
		fprintf(fp,"%s\n",seitomei[i]);
	}
	printf("%sにデータ保存完了\n",savename);
}


void continuation(){
	int o;
	printf("-----CONTINUE MENU-----\n");
	printf("1.追加\n");
	printf("2.変更\n");
	printf("3.確認\n");
	printf("4.分布図表示\n");
	printf("Choose number:");
	scanf("%d",&o);
	printf("-----------------------\n");
	if(o==1)add();
	else if(o==2)change();
	else if(o==3)check();
	else if(o==4)figure();
	else printf("illeagal number...");
}

void read(){
	char loadname[100];
	printf("ロードしたい「年度-学年-クラス」を入力:");
	scanf("%s",loadname);
	FILE *fp;
	
	fp=fopen(loadname,"r");
	if(fp==NULL){
		printf("%s file not open!",loadname);
		exit(0);
	}
	//各種変数入力
	fscanf(fp,"%d %d",&stu,&sub);
	
	//成績入力
	for(i=1;i<=stu+1;i++){
		for(t=1;t<=sub+1;t++){
			fscanf(fp,"%f",&seiseki[i][t]);	
		}
	}
	
	//順位入力
	for(i=1;i<=stu;i++){
		for(t=1;t<=sub+1;t++){
			fscanf(fp,"%d",&juni[i][t]);
		}
	}
	
	//科目名入力
	for(i=1;i<=sub;i++){
		fscanf(fp,"%s",kamokumei[i]);
	}
	
	//生徒名入力
	for(i=1;i<=stu;i++){
		fscanf(fp,"%s",seitomei[i]);
	}	
	continuation();
}

void add(){
	int o,m;
	printf("-----ADD MENU-----\n");
	printf("1.生徒追加\n");
	printf("2.科目追加\n");
	printf("Choose Number:");
	scanf("%d",&o);
	printf("------------------\n");
	if(o==1){
		stu++;
		printf("生徒名を入力:");
		scanf("%s",seitomei[stu]);
		for(m=1;m<=sub;m++){
			printf("%sの%sの点数を入力:",seitomei[stu],kamokumei[m]);
			scanf("%f",&seiseki[stu][m]);
			if(seiseki[stu][m]>100)seiseki[stu][m]=100;
		}
	}else if(o==2){
		sub++;
		printf("科目名を入力:");
		scanf("%s",kamokumei[sub]);
		for(m=1;m<=stu;m++){
			printf("%sの%sの点数を入力:",seitomei[m],kamokumei[sub]);
			scanf("%f",&seiseki[m][sub]);
			if(seiseki[m][sub]>100)seiseki[m][sub]=100;
		}
	}else printf("illeagal....");
	ave();
	printf("-----SAVE MENU-----\n");
		printf("保存しますか？");
		printf("1.保存\n");
		printf("2.保存しない\n");
		printf("Choose:");
		scanf("%d",&i);
		printf("-------------------\n");
		if(i==1)save();
}

void change(){
	int a,b;
	printf("-----CHANGE MENU-----\n");
	for(a=1;a<=stu;a++){
		printf("%d.%s",a,seitomei[a]);
	}
	printf("変更したい生徒番号を入力:");
	scanf("%d",&b);
	for(a=1;a<=sub;a++){
		printf("%d.%s",a,kamokumei[a]);
	}
	printf("変更したい科目番号を入力:");
	scanf("%d",&a);
	printf("---------------------\n");
	printf("%sの%sの新しい点数を入力（現在は%.0f）:",seitomei[b],kamokumei[a],seiseki[b][a]);
	scanf("%f",&seiseki[b][a]);
	ave();
		printf("-----SAVE MENU-----\n");
		printf("保存しますか？");
		printf("1.保存\n");
		printf("2.保存しない\n");
		printf("Choose:");
		scanf("%d",&i);
		printf("-------------------\n");
		if(i==1)save();
}

void figure(){
	int bunpu[101];
	int max,tate,nin,ten,in;
	FILE *fp,*gp;
	
	max=0;
	printf("-----FIGURE MENU-----\n");
	for(tate=1;tate<=stu;tate++){
		printf("%d %s\n",tate,kamokumei[tate]);
	}
	printf("%d 総合平均\n",tate);
	printf("表示したい科目番号を入力してください：");
	scanf("%d",&in);
	printf("---------------------\n");
	if(in>=1 && in<=sub+1){
		for(tate=0;tate<=100;tate++){
			bunpu[tate]=0;
		}
		for(tate=1;tate<=stu;tate++){
			ten=seiseki[tate][in];
			bunpu[ten]+=1;
		}
		for(tate=1;tate<=100;tate++){
			if(max<bunpu[tate]){
				max=bunpu[tate];
			}
		}
		max+=5;
		fp=fopen("gnuplot.csv","w");
		for(tate=0;tate<=100;tate++){
			fprintf(fp,"%d %d\n",tate,bunpu[tate]);
		}
		fclose(fp);
	
		gp=popen("gnuplot -persist","w");
		fprintf(gp,"set xrange[0:100]\n");
		fprintf(gp,"set yrange[0:%d]\n",max);
		fprintf(gp,"set xlabel 'Score'\n");
		fprintf(gp,"set ylabel 'Number of people'\n");
		fprintf(gp,"plot \"gnuplot.csv\" using 1:2 with linespoints\n");
		pclose(gp);
	}
	continuation();
}
