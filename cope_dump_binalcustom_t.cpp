#include <iostream>
#include <fstream>
#include <math.h>
#include<string>
using namespace std;

int main(){
   int a,b;    //fortranで書かれたものはヘッダとフッタがついている。前と後ろにそれぞれ4byteずつ,読み込ませておいて捨てる
   double xu,yu,z,u,v,w,e;//データが6つあるから6つ用意//エネルギーも追加171016  
   double xd,yd;
   int vec_x;
   int vec_y;
   /*   int tempo_counter[16][16];
   for(int i=0;i<15;i++)
     {
       for(int j=0;j<15;j++)
	 {
	   tempo_counter[i][j]=0;
	 }
     }
   */

   double ds=13.4;//検出器のサイズ                                               
   double half;//検出器の半分                                                    
   double pix=16.;//ピクセル数                                                    
   double divide;//検出器をピクセル等分する                                      
   double height=15.;//検出器の間隔 
   // int counter[31][31];                                              
   double cutenergy=10000000;//あるエネルギー以下は使わないという閾値
   divide=ds/pix;
   half=ds/2.0;

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
   ofst.open("compress15.txt",ios::app);// 
   
   std::ofstream spectrum1;
   spectrum1.open("energyspectrum44.txt");
std::ofstream spectrum2;	
   spectrum2.open("energyspectrum4-4.txt");
std::ofstream spectrum3;
   spectrum3.open("energyspectrum-44.txt");//今は使ってないから
std::ofstream spectrum4;
   spectrum4.open("energyspectrum-4-4.txt");//今は使ってないから 

   int cc=0;  //ccは検出器上面で検出された粒子の数を数えている
   for(int filenumber=1;filenumber<6;filenumber++)
     {
       char outfile[] = "cross_reg_dmp.out.001";  //読み込むファイルの指定   
       char numb_1,numb_10;
       if(filenumber<10)
	 {
	   numb_1='0'+filenumber;
	   outfile[20]=numb_1;  //読み込むファイルの指定                  
	   cout<<outfile<<endl;
	 }
       else{
	 numb_1='0'+filenumber-10;
	 numb_10='0'+filenumber/10;
	 outfile[19]=numb_10;
	 outfile[20]=numb_1;  //読み込むファイルの指定                  
	 cout<<outfile<<endl;
       }
       
       ifstream fin( outfile, ios::in | ios::binary );
       //  ファイルを開く
       //  ios::in は読み込み専用  ios::binary はバイナリ形式
       
       if (!fin){
	 cout << "ファイル file.txt が開けません";
	 return 1;
   }
       //  ファイルが開けなかったときの対策
       
       while(!fin.eof())
   {  //ファイルの最後まで続ける
       fin.read( ( char * ) &a, sizeof( int ) );//ヘッダ
       fin.read( ( char * ) &xu, sizeof( double ) );
       fin.read( ( char * ) &yu, sizeof( double ) );
       fin.read( ( char * ) &z, sizeof( double ) );
       fin.read( ( char * ) &u, sizeof( double ) );
       fin.read( ( char * ) &v, sizeof( double ) );
       fin.read( ( char * ) &w, sizeof( double ) );
       fin.read( ( char * ) &e, sizeof( double ) );//energy
       fin.read( ( char * ) &b, sizeof( int ) );//フッタ                               
       
       //       cout<<e<<endl;
       //   cout<<xu<<" "<<yu<<" "<<z<<" "<<e<<endl;
       if(e<cutenergy)
	 {       
	   xd=xu+u*(height/-w);
	   yd=yu+v*(height/-w);//下の検出器があったとしたらどの位置に来るか                                                                      
	   cc=cc+1;
	   //  cout<<xu<<" "<<yu<<" "<<xd<<" "<<yd<<endl;           
	   if(-ds/2.<=xd && xd<=ds/2. && -ds/2.<=yd && yd<=ds/2.)//もし、両方の検出器を通過しない場合は無視      
	 {
	   
	   
	   //	   cout<<e<<endl;  
	   if(-half+divide*0.<=xu && xu<-half+divide*1.)//座標からピクセルに割り振る、ここをもっときれいにしたい                                    
	     { xu=0.;}
	   else if(-half+divide*1.<=xu && xu<-half+divide*2.)
	     { xu=1.;}
	   else if(-half+divide*2.<=xu && xu<-half+divide*3.)
	     { xu=2.;}
	   else if(-half+divide*3.<=xu && xu<-half+divide*4.)
	     { xu=3.;}
	   else if(-half+divide*4.<=xu && xu<-half+divide*5.)
	     { xu=4.;}
	   else if(-half+divide*5.<=xu && xu<-half+divide*6.)
	     { xu=5.;}
	   else if(-half+divide*6.<=xu && xu<-half+divide*7.)
	     { xu=6.;}
	   else if(-half+divide*7.<=xu && xu<-half+divide*8.)
	     { xu=7.;}
	   else if(-half+divide*8.<=xu && xu<-half+divide*9.)
	     { xu=8.;}
	   else if(-half+divide*9.<=xu && xu<-half+divide*10.)
	     { xu=9.;}
	   else if(-half+divide*10.<=xu && xu<-half+divide*11.)
	     { xu=10.;}
	   else if(-half+divide*11.<=xu && xu<-half+divide*12.)
	     { xu=11.;}
	   else if(-half+divide*12.<=xu && xu<-half+divide*13.)
	     { xu=12.;}
	   else if(-half+divide*13.<=xu && xu<-half+divide*14.)
	     { xu=13.;}
	   else if(-half+divide*14.<=xu && xu<-half+divide*15.)
	     { xu=14.;}
	   else if(-half+divide*15.<=xu && xu<=-half+divide*16.)
	     { xu=15.;}
	   
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
	   
	   
	   if(-half+divide*0.<=yu && yu<-half+divide*1.)
	     { yu=0.;}
	   else if(-half+divide*1.<=yu && yu<-half+divide*2.)
	     { yu=1.;}
	   else if(-half+divide*2.<=yu && yu<-half+divide*3.)
	     { yu=2.;}
	   else if(-half+divide*3.<=yu && yu<-half+divide*4.)
	     { yu=3.;}
	   else if(-half+divide*4.<=yu && yu<-half+divide*5.)
	     { yu=4.;}
	   else if(-half+divide*5.<=yu && yu<-half+divide*6.)
	     { yu=5.;}
	   else if(-half+divide*6.<=yu && yu<-half+divide*7.)
	     { yu=6.;}
	   else if(-half+divide*7.<=yu && yu<-half+divide*8.)
	     { yu=7.;}
	   else if(-half+divide*8.<=yu && yu<-half+divide*9.)
	     { yu=8.;}
	   else if(-half+divide*9.<=yu && yu<-half+divide*10.)
	     { yu=9.;}
	   else if(-half+divide*10.<=yu && yu<-half+divide*11.)
	     { yu=10.;}
	   else if(-half+divide*11.<=yu && yu<-half+divide*12.)
	     { yu=11.;}
	   else if(-half+divide*12.<=yu && yu<-half+divide*13.)
	     { yu=12.;}
	   else if(-half+divide*13.<=yu && yu<-half+divide*14.)
	     { yu=13.;}
	   else if(-half+divide*14.<=yu && yu<-half+divide*15.)
	     { yu=14.;}
	   else if(-half+divide*15.<=yu && yu<=-half+divide*16.)
	     { yu=15.;}
	   
	   
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
	   
	   // cout<<xu<<" "<<yu<<" "<<xd<<" "<<yd<<endl;
	   // cout<<e<<endl;
	   // spectrum<<e<<endl;//energyspectrum.txt
	   // int xxuu,yyuu;
	   vec_x=round(xu-xd);//ベクトルを求める                                                                                                                                                            
	   vec_y=-round(yu-yd);//ベクトルを求める                                                                                                                                                         
	   // cout<<vec_x<<" "<<vec_y<<endl;
	   // ofs<<vec_x<<" "<<vec_y<<endl;//hist_data2.txt
	   // ofstr<<yu<<" "<<xu+16<<" "<<yd+32<<" "<<xd+48<<" "<<endl;
	   /*
	   if((vec_x==3 ||vec_x==4) && (vec_y==-4 || vec_y==-3))
	     {
	       spectrum1<<e<<endl;
	     }
	 if(vec_x==4 && vec_y==-4)
	   {
	     spectrum2<<e<<endl;
	   }
	 if(vec_x==-4 && vec_y==4)
	   {
	     spectrum3<<e<<endl;
	   }
	 if(vec_x==-4 && vec_y==-4)
	     {
	       spectrum4<<e<<endl;
	       }
	   */
	 counter[vec_x][vec_y]++;//それぞれのベクトルに入るベクトルがそれぞれ何個あるか
	 
	 // ofs.write((char *) &vec_x,sizeof(int));
	 // ofs.write((char *) &vec_y,sizeof(int));
	 }
	   // fin.close();  //ファイルを閉じる	
	 }
   }
       
     }
   
   
   
   int c=0;//cはコインシデンスを考慮したうえでの粒子数
   for(int i=-n;i<n+1;i++)
     {
       for(int j=-n;j<n+1;j++)
	 {
	 // cout<<i<<" "<<j<<" "<<counter[i][j]<<endl;
	   ofst<<i<<" "<<j<<" "<<counter[i][j]<<endl;//compress.txt
	   c=c+counter[i][j];
	 }
     }
   
   
  std::ofstream temp;
  temp.open("tempo.txt");
  for(int i=0;i<16;i++)
    {
      for(int j=0;j<16;j++)
	{
	  //	  temp<<i<<" "<<j<<" "<<tempo_counter[i][j]<<endl;
	}
    }
  
  // std::ofstream rate;
  // rate.open("degree.txt");//171109角度ごとの強度をまとめた
  std::ofstream time_estimation("time_estimation.txt");
  time_estimation<<"Upper_detector_count "<<cc<<"Coincidence_count "<<c<<endl;
  time_estimation<<"time="<<cc/(ds*ds*60*24)<<" hours"<<endl;
 
  cout<<cc<<" "<<c<<" "<<counter[0][0]<<endl;
  //  cout<<"10deg="<<tendigcounter<<endl;//171109
  // cout<<"20deg="<<twedigcounter<<endl;//171109
  // cout<<"30deg="<<thrdigcounter<<endl;//171109
  // cout<<"40deg="<<fourdigcounter<<endl;//171109
  // cout<<"50deg="<<fifdigcounter<<endl;///171109
  // cout<<"60deg="<<sixtdigcounter<<endl;//171109
  // cout<<"70deg="<<seventdigcounter<<endl;//171109
  // cout<<"80deg="<<eightydigcounter<<endl;//171109

  // rate<<tendigcounter<<endl;//171109                                                                                                                                                                     
  // rate<<twedigcounter<<endl;//171109                                                                                                                                                                     
  // rate<<thrdigcounter<<endl;//171109                                                                                                                                                                     
  // rate<<fourdigcounter<<endl;//171109                                                                                                                                                                    
  // rate<<fifdigcounter<<endl;///171109                                                                                                                                                                    
  // rate<<sixtdigcounter<<endl;//171109                                                                                                                                                                    
  // rate<<seventdigcounter<<endl;//171109                                                                                                                                                                  
  // rate<<eightydigcounter<<endl;//171109 
 
  
  return 0;
}
  
