#include <iostream>
#include <fstream>
#include <math.h>
#include<string>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <dirent.h>
using namespace std; //define the nemespase

bool StrString(const char *s1,const char *s2);

int main(){
   int a,b;    //ヘッダとフッタ読込用
   double x,y,z,vx,vy,vz,e;
   double xd,yd;
   int vec_x;
   int vec_y;
   double ds;//検出器のサイズ
   double half;//検出器の半分
   double pix;//ピクセル数
   double divide;//検出器をピクセル等分する
   double height;//検出器の間隔
   double cutenergy=1000000000;//cutenergy

   int detector_type;
   cout << "Please select proto or ImpDet" << endl <<"Proto  : 1" << endl << "ImpDet : 2" << endl << ">>";
   cin >> detector_type;

   if(detector_type == 1){
   cout << "You selected prottype." << endl;
   ds=13.4;//検出器のサイズ
   pix=16.;//ピクセル数
   height=10.;//検出器の間隔
   }
   else if(detector_type == 2){
   cout << "You selected Improved Detector." << endl;
   ds=28.8;//the size of detector
   pix=16.;//nambers of pixel
   height=22.;//length btween tow detector
   }
   else{
   cout << "You should select 1 or 2." << endl;
   }

   divide=ds/pix;
   half=ds/2.0;
   
   string output;
   cout << "Input output file name >>" << endl;
   cin  >> output; 

   int n=15;
   double **dummy1=new double*[2*n+1];
   double  *dummy2=new double[(2*n+1)*(2*n+1)];
   dummy1[0]=dummy2+n;
   for(int i=1;i<2*n+1;i++)
     {
       dummy1[i]=dummy1[i-1]+2*n+1;
     }
   double **counter=dummy1+n;//counterという2次元配列を負の領域に解放

   for(int i=-n;i<n+1;i++)
     for(int j=-n;j<n+1;j++)
	{
	 counter[i][j]=0;//初期化
	}

   std::ofstream ofst;
   ofst.open(output.c_str());//データを書き出すファイル

 int cc=0;  //ccは検出器上面で検出された粒子の数を数えている

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////ファイル名の取得
    stringstream ss1;

    const char* path="./";//文字列型
    DIR *dp;//ファイル一覧を取得
    dirent* entry;
    string filename[4096];
    int filenum=0;
    dp = opendir(path);//path以下のやつを全部開く

    while((entry=readdir(dp))!=NULL)
      {
	string tmp;
	tmp=entry -> d_name;
	cout<<tmp<<endl;
	if(StrString(tmp.c_str(),"dmp"))
	  {
	    filename[filenum]=tmp;

	    cout<<tmp<<" "<<filenum<<" "<<filename[filenum]<<endl;
	    filenum++;
	  }
      }
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////ファイルをひとずつ開いていく
for(int i=0; i<filenum; i++)
{
  ifstream fin( filename[i].c_str(), ios::in | ios::binary ); //ios::in は読み込み専用 ios::binary はバイナリ形式

       if (!fin)
       {
	 cout << "ファイル file.txt が開けません";
	 return 1;
	}

       while(!fin.eof())
	{ 
       fin.read( ( char * ) &a, sizeof( int ) );//ヘッダ
       fin.read( ( char * ) &x, sizeof( double ) );//x座標
       fin.read( ( char * ) &y, sizeof( double ) );//y座標
       fin.read( ( char * ) &z, sizeof( double ) );//z座標
       fin.read( ( char * ) &vx, sizeof( double ) );//x方向の運動量
       fin.read( ( char * ) &vy, sizeof( double ) );//y方向の運動量
       fin.read( ( char * ) &vz, sizeof( double ) );//z方向の運動量
       fin.read( ( char * ) &e, sizeof( double ) );//energy
       fin.read( ( char * ) &b, sizeof( int ) );//フッタ

       if(e<cutenergy)
	 {
	   xd=x+vx*(height/-vz);
	   yd=y+vy*(height/-vz);//下の検出器があったとしたらどの位置に来るか
	   cc=cc+1;
	   if(-ds/2.<=xd && xd<=ds/2. && -ds/2.<=yd && yd<=ds/2.)//もし、両方の検出器を通過しない場合は無視
	 {
	   if(-half+divide*0.<=x && x<-half+divide*1.)//ピクセルに割当
	     { x=0.;}
	   else if(-half+divide*1.<=x && x<-half+divide*2.)
	     { x=1.;}
	   else if(-half+divide*2.<=x && x<-half+divide*3.)
	     { x=2.;}
	   else if(-half+divide*3.<=x && x<-half+divide*4.)
	     { x=3.;}
	   else if(-half+divide*4.<=x && x<-half+divide*5.)
	     { x=4.;}
	   else if(-half+divide*5.<=x && x<-half+divide*6.)
	     { x=5.;}
	   else if(-half+divide*6.<=x && x<-half+divide*7.)
	     { x=6.;}
	   else if(-half+divide*7.<=x && x<-half+divide*8.)
	     { x=7.;}
	   else if(-half+divide*8.<=x && x<-half+divide*9.)
	     { x=8.;}
	   else if(-half+divide*9.<=x && x<-half+divide*10.)
	     { x=9.;}
	   else if(-half+divide*10.<=x && x<-half+divide*11.)
	     { x=10.;}
	   else if(-half+divide*11.<=x && x<-half+divide*12.)
	     { x=11.;}
	   else if(-half+divide*12.<=x && x<-half+divide*13.)
	     { x=12.;}
	   else if(-half+divide*13.<=x && x<-half+divide*14.)
	     { x=13.;}
	   else if(-half+divide*14.<=x && x<-half+divide*15.)
	     { x=14.;}
	   else if(-half+divide*15.<=x && x<=-half+divide*16.)
	     { x=15.;}

	   if(-half+divide*0.<=xd && xd<-half+divide*1.)
	     { xd=0.;}
	   else if(-half+divide*1.<=xd && xd<-half+divide*2.)
	     { xd=1.;}
	   else if(-half+divide*2.<=xd && xd<-half+divide*3.)
	     { xd=2.;}
	   else if(-half+divide*3.<=xd && xd<-half+divide*4.)
	     { xd=3.;}
	   else if(-half+divide*4.<=xd && xd<-half+divide*5.)
	     { xd=4.;}
	   else if(-half+divide*5.<=xd && xd<-half+divide*6.)
	     { xd=5.;}
	   else if(-half+divide*6.<=xd && xd<-half+divide*7.)
	     { xd=6.;}
	   else if(-half+divide*7.<=xd && xd<-half+divide*8.)
	     { xd=7.;}
	   else if(-half+divide*8.<=xd && xd<-half+divide*9.)
	     { xd=8.;}
	   else if(-half+divide*9.<=xd && xd<-half+divide*10.)
	     { xd=9.;}
	   else if(-half+divide*10.<=xd && xd<-half+divide*11.)
	     { xd=10.;}
	   else if(-half+divide*11.<=xd && xd<-half+divide*12.)
	     { xd=11.;}
	   else if(-half+divide*12.<=xd && xd<-half+divide*13.)
	     { xd=12.;}
	   else if(-half+divide*13.<=xd && xd<-half+divide*14.)
	     { xd=13.;}
	   else if(-half+divide*14.<=xd && xd<-half+divide*15.)
	     { xd=14.;}
	   else if(-half+divide*15.<=xd && xd<=-half+divide*16.)
	     { xd=15.;}

	   if(-half+divide*0.<=y && y<-half+divide*1.)
	     { y=0.;}
	   else if(-half+divide*1.<=y && y<-half+divide*2.)
	     { y=1.;}
	   else if(-half+divide*2.<=y && y<-half+divide*3.)
	     { y=2.;}
	   else if(-half+divide*3.<=y && y<-half+divide*4.)
	     { y=3.;}
	   else if(-half+divide*4.<=y && y<-half+divide*5.)
	     { y=4.;}
	   else if(-half+divide*5.<=y && y<-half+divide*6.)
	     { y=5.;}
	   else if(-half+divide*6.<=y && y<-half+divide*7.)
	     { y=6.;}
	   else if(-half+divide*7.<=y && y<-half+divide*8.)
	     { y=7.;}
	   else if(-half+divide*8.<=y && y<-half+divide*9.)
	     { y=8.;}
	   else if(-half+divide*9.<=y && y<-half+divide*10.)
	     { y=9.;}
	   else if(-half+divide*10.<=y && y<-half+divide*11.)
	     { y=10.;}
	   else if(-half+divide*11.<=y && y<-half+divide*12.)
	     { y=11.;}
	   else if(-half+divide*12.<=y && y<-half+divide*13.)
	     { y=12.;}
	   else if(-half+divide*13.<=y && y<-half+divide*14.)
	     { y=13.;}
	   else if(-half+divide*14.<=y && y<-half+divide*15.)
	     { y=14.;}
	   else if(-half+divide*15.<=y && y<=-half+divide*16.)
	     { y=15.;}

	   if(-half+divide*0.<=yd && yd<-half+divide*1)
	     { yd=0.;}
	   else if(-half+divide*1.<=yd && yd<-half+divide*2.)
	     { yd=1.;}
	   else if(-half+divide*2.<=yd && yd<-half+divide*3.)
	     { yd=2.;}
	   else if(-half+divide*3.<=yd && yd<-half+divide*4.)
	     { yd=3.;}
	   else if(-half+divide*4.<=yd && yd<-half+divide*5.)
	     { yd=4.;}
	   else if(-half+divide*5.<=yd && yd<-half+divide*6.)
	     { yd=5.;}
	   else if(-half+divide*6.<=yd && yd<-half+divide*7.)
	     { yd=6.;}
	   else if(-half+divide*7.<=yd && yd<-half+divide*8.)
	     { yd=7.;}
	   else if(-half+divide*8.<=yd && yd<-half+divide*9.)
	     { yd=8.;}
	   else if(-half+divide*9.<=yd && yd<-half+divide*10.)
	     { yd=9.;}
	   else if(-half+divide*10.<=yd && yd<-half+divide*11.)
	     { yd=10.;}
	   else if(-half+divide*11.<=yd && yd<-half+divide*12.)
	     { yd=11.;}
	   else if(-half+divide*12.<=yd && yd<-half+divide*13.)
	     { yd=12.;}
	   else if(-half+divide*13.<=yd && yd<-half+divide*14.)
	     { yd=13.;}
	   else if(-half+divide*14.<=yd && yd<-half+divide*15.)
	     { yd=14.;}
	   else if(-half+divide*15.<=yd && yd<=-half+divide*16.)
	     { yd=15.;}
	   // cout<<x<<" "<<y<<" "<<xd<<" "<<yd<<endl;
	   // cout<<e<<endl;
	   // spectrum<<e<<endl;//energyspectrum.txt
	   // int xxu,yyu;
	   vec_x=round(x-xd);//ベクトルを求める
	   vec_y=-round(y-yd);//ベクトルを求める
	   counter[vec_x][vec_y]++;

	 }
	 }
	}
}
//ファイル読込の終わり

   ofst<<100<<" "<<100<<" "<<cc/(ds*ds*60)<<endl;
   int c=0;//cはコインシデンスを考慮したうえでの粒子数
   for(int i=-n;i<n+1;i++)
     {
       for(int j=-n;j<n+1;j++)
	 {
	   ofst<<i<<" "<<j<<" "<<int(counter[i][j])<<endl;//compress.txt
	   c=c+counter[i][j];
	 }
     }
  
  std::ofstream time_estimation("time_estimation.txt");
  time_estimation<<"Upper_detector_count "<<cc<<"Coincidence_count "<<c<<endl;
  time_estimation<<"time="<<cc/(ds*ds*60)<<" hours"<<endl;



  cout<<cc<<" "<<c<<endl;

  return 0;
}

bool StrString(const char*s1,const char *s2)//文字の一致を調べる
{
  int n;
  n=strlen(s2);
  while(1){
    s1=strchr(s1,s2[0]);//s1の最初からs2[0]の文字を探す
    if(s1==NULL)
      return false;
    if(strncmp(s1,s2,n)==0)//s1とs2を前からn文字分比べる、s1=s2の場合0を返す
      return true;
    s1++;
  }
}
