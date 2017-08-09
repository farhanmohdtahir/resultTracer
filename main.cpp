#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <sstream>
using namespace std;

struct rng{
    string totalReadRng,noSubs, subs;
    int totalReadCnt, noSubsCnt, subsCnt, softClipCnt, noMapCnt, misMapCnt, trueMapCnt, softClipCntSubs, trueMapCntSubs, misMapCntSubs, noMapCntSubs;
};

int main(){
    ifstream infile1, infile2, infile3;
    ofstream outfile;
    int totalRef=0, i=0, j=0, k=0, l=0, m=0, n=0;
    string in1="expected_hsa.txt", in2="output_hsa.sam", out="result.txt", line, lineTemp, lineIden;
    int lineIdenFirst[20000], lineIdenSec[20000];
    bool newObj;

    infile1.open(in1.c_str());
        while(getline(infile1, line)){
            if(line[0]=='@') ++totalRef;
        }

    string header[totalRef], totalRead[totalRef], noSubsMap[totalRef], subsMap[totalRef], subsBaseNum[totalRef], id[totalRef], subsLineStr;
    std::string::size_type sz;
    // int totalReadCnt[totalRef], noSubsCnt[totalRef], subsCnt[totalRef], softClipCnt[totalRef], noMapCnt[totalRef], misMapCnt[totalRef];
    rng a[totalRef],b[totalRef],c[totalRef],d[totalRef],e[totalRef],f[totalRef];
    int subsLine[totalRef][30];

    infile2.open(in1.c_str());
        while(getline(infile2, line)){
            if(line[0]=='@'){
                line.erase(find(line.begin(), line.end(), '@'));
                header[i]=line;
                for (j=0; j<line.length(); j++){
                    if (line[j]==';')break;
                    id[i]+=line[j];
                }
            }
            else if(line[0]=='#'){
                j=0;
                for(k=0; k<line.length(); k++){
                    if (k>0){
                        if(line[k]!='+'){
                            subsLineStr+=line[k];
                            stringstream(subsLineStr) >> subsLine[i][j];
                        }
                        else{
                            ++j;
                            subsLineStr="";
                        }
                    }
                }
                // cout<<subsLine[i][j];
            }
            else if (line[0]=='\0'){}
            else{  
                k=0;
                for (j=0; j<line.length(); j++){
                    if (line[j]=='+')++k;
                    else {
                        switch(k){
                            case 0:
                                a[i].totalReadRng+=line[j];
                                break;
                            case 1:
                                b[i].totalReadRng+=line[j];
                                break;
                            case 2:
                                c[i].totalReadRng+=line[j];
                                break;
                            case 3:
                                d[i].totalReadRng+=line[j];
                                break;
                            case 4:
                                e[i].totalReadRng+=line[j];
                                break;
                            case 5:
                                f[i].totalReadRng+=line[j];
                                break;
                            case 6:
                                a[i].noSubs+=line[j];
                                break;
                            case 7:
                                b[i].noSubs+=line[j];
                                break;
                            case 8:
                                c[i].noSubs+=line[j];
                                break;
                            case 9:
                                d[i].noSubs+=line[j];
                                break;
                            case 10:
                                e[i].noSubs+=line[j];
                                break;
                            case 11:
                                f[i].noSubs+=line[j];
                                break;
                           case 12:
                                a[i].subs+=line[j];
                                break;
                            case 13:
                                b[i].subs+=line[j];
                                break;
                            case 14:
                                c[i].subs+=line[j];
                                break;
                            case 15:
                                d[i].subs+=line[j];
                                break;
                            case 16:
                                e[i].subs+=line[j];
                                break;
                            case 17:
                                f[i].subs+=line[j];
                                break;                            
                        }
                    }
                    // cout<<k<<" ";
                }
                ++i;
            }
            subsLineStr="";
        }

        int totSamLine=100;
        string readHead[totalRef][totSamLine], readLen[totalRef][totSamLine], softClip[totalRef][totSamLine], subsDet[totalRef][totSamLine];

        // string simRead[totalRef][100];  
        lineTemp=header[0];
        
        infile1.close();
        infile2.close();
//----------------------------------------------------------------------------------------------------------------------------
        infile3.open(in2.c_str());
        i=0;l=0;
        while(getline(infile3, line)){
                                        // cout<<line.length()<<endl;
            if (line[0]==lineTemp[0]&&line[1]==lineTemp[1]){
            k=0;
                        for (j=0; j<line.length(); j++){
                            if (line[j]=='\t')++k;
                            else {
                                if (k==0) readHead[i][l]+=line[j];
                                if (k==1){
                                    if (l>0){
                                        if (readHead[i][l]!=readHead[i][l-1]){
                                        ++i;
                                        readHead[i][0]=readHead[i-1][l];
                                        l=0;
                                        }
                                    }
                                }
                                else if(k==2) lineIden+=line[j];
                                else if (k==3){
                                    if(lineIden!="*"){
                                        if (lineIden!=readHead[i][l]){
                                    // cout<<lineIden<<" "<<readHead[i][l]<<endl;
                                            lineIdenFirst[n]=i;
                                            lineIdenSec[n]=l;
                                            ++n;
                                        }
                                    }
                                }
                                else if (k==5) softClip[i][l]+=line[j];
                                else if (k==9) readLen[i][l]+=line[j]; 
                                else if (k==15) subsDet[i][l]+=line[j];
                            }
                        }
                    lineIden="";
                    // cout<<i<<" "<<l<<endl;
                    ++l;           
            }
        }

        // cout<<softClip[0][2]<<"  "<<softClip[1][2];
        // for(i=0; i<n; i++){
        //     cout<<lineIdenFirst[i]<<" "<<lineIdenSec[i]<<endl;
        // }
        // cout<<n;
        // cout<<softClip[1][99]<<" "<<softClip[2][0];
        infile3.close();
 
    // for (i=0; i<totalRef; i++){cout<<i<<"\t"<<softClip[i][3]<<endl;}
//-----------------------------------------------------------------------------------------------------------------------------
        j=0;
        n=0;
        for (i=0; i<totalRef; i++){
            m=0;
            for (int l=0; l<totSamLine; l++){
                if (readLen[i][l].length()==17){
                                            // cout<<i<<" "<<l<<endl;
                     if(readHead[i][l]==id[j]){
                        ++a[j].totalReadCnt;
                        if(l==subsLine[i][m]){
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++a[j].trueMapCntSubs;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++a[j].misMapCntSubs;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++a[j].softClipCntSubs;
                            else if (softClip[i][l]=="*") ++a[j].noMapCntSubs;
                           // else ++a[j].trueMapCntSubs;  
                            ++m;
                        }
                        else{
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) {}//++a[j].trueMapCnt;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++a[j].misMapCnt;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) {++a[j].softClipCnt;if(i==1){cout<<l<<","<<subsLine[i][m]<<" "<<i<<m<<"\t";}}
                            else if (softClip[i][l]=="*") ++a[j].noMapCnt;
                            else ++a[j].trueMapCnt;       
                        }
                        // if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                        //     ++a[j].misMapCnt;
                        //     ++n;
                        // }
                        // else if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                        // strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++a[j].subsCnt;                      
                        // else if (strchr(softClip[i][l].c_str(), 'S')) ++a[j].softClipCnt;
                        // else if (softClip[i][l]=="*") ++a[j].noMapCnt;
                        // else ++a[j].noSubsCnt;       
                                    
                    }
                }

                if (readLen[i][l].length()==18){
                                            // cout<<i<<" "<<l<<endl;
                     if(readHead[i][l]==id[j]){
                        ++b[j].totalReadCnt;
                        if(l==subsLine[i][m]){
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++b[j].trueMapCntSubs;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++b[j].misMapCntSubs;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++b[j].softClipCntSubs;
                            else if (softClip[i][l]=="*") ++b[j].noMapCntSubs;
                            //else ++b[j].trueMapCntSubs;  
                            ++m;
                        }
                        else{
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')){} //++b[j].trueMapCnt;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++b[j].misMapCnt;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++b[j].softClipCnt;
                            else if (softClip[i][l]=="*") ++b[j].noMapCnt;
                            else ++b[j].trueMapCnt;       
                        }
                    }
                }

                if (readLen[i][l].length()==19){
                                            // cout<<i<<" "<<l<<endl;
                     if(readHead[i][l]==id[j]){
                        ++c[j].totalReadCnt;
                        if(l==subsLine[i][m]){
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++c[j].trueMapCntSubs;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++c[j].misMapCntSubs;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++c[j].softClipCntSubs;
                            else if (softClip[i][l]=="*") ++c[j].noMapCntSubs;
                            //else ++c[j].trueMapCntSubs;  
                            ++m;
                        }
                        else{
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')){}// ++c[j].trueMapCnt;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++c[j].misMapCnt;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++c[j].softClipCnt;
                            else if (softClip[i][l]=="*") ++c[j].noMapCnt;
                            else ++c[j].trueMapCnt;       
                        }
                    }
                }

                if (readLen[i][l].length()==20){
                                            // cout<<i<<" "<<l<<endl;
                     if(readHead[i][l]==id[j]){
                        ++d[j].totalReadCnt;
                        if(l==subsLine[i][m]){
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++d[j].trueMapCntSubs;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++d[j].misMapCntSubs;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++d[j].softClipCntSubs;
                            else if (softClip[i][l]=="*") ++d[j].noMapCntSubs;
                           // else ++d[j].trueMapCntSubs;  
                            ++m;
                        }
                        else{
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) {}//++d[j].trueMapCnt;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++d[j].misMapCnt;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++d[j].softClipCnt;
                            else if (softClip[i][l]=="*") ++d[j].noMapCnt;
                            else ++d[j].trueMapCnt;       
                        }
                    }
                }

                if (readLen[i][l].length()==21){
                                            // cout<<i<<" "<<l<<endl;
                     if(readHead[i][l]==id[j]){
                        ++e[j].totalReadCnt;
                        if(l==subsLine[i][m]){
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++e[j].trueMapCntSubs;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++e[j].misMapCntSubs;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++e[j].softClipCntSubs;
                            else if (softClip[i][l]=="*") ++e[j].noMapCntSubs;
                           // else ++e[j].trueMapCntSubs;  
                            ++m;
                        }
                        else{
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) {}//++e[j].trueMapCnt;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++e[j].misMapCnt;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++e[j].softClipCnt;
                            else if (softClip[i][l]=="*") ++e[j].noMapCnt;
                            else ++e[j].trueMapCnt;       
                        }
                    }
                }

                if (readLen[i][l].length()==22){
                                            // cout<<i<<" "<<l<<endl;
                     if(readHead[i][l]==id[j]){
                        ++f[j].totalReadCnt;
                        if(l==subsLine[i][m]){
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++f[j].trueMapCntSubs;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++f[j].misMapCntSubs;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++f[j].softClipCntSubs;
                            else if (softClip[i][l]=="*") ++f[j].noMapCntSubs;
                          //  else ++f[j].trueMapCntSubs;  
                            ++m;
                        }
                        else{
                            if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                            strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) {}//++f[j].trueMapCnt;
                            else if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                                ++f[j].misMapCnt;
                                ++n;
                            }                     
                            else if (strchr(softClip[i][l].c_str(), 'S')) ++f[j].softClipCnt;
                            else if (softClip[i][l]=="*") ++f[j].noMapCnt;
                            else ++f[j].trueMapCnt;       
                        }
                    }
                }

                // else if (readLen[i][l].length()==18){
                //      if(readHead[i][l]==id[j]){
                //         ++b[j].totalReadCnt;
                //         if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                //             ++b[j].misMapCnt;
                //             ++n;
                //         }
                //         else if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                //         strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++b[j].subsCnt;                      
                //         else if (strchr(softClip[i][l].c_str(), 'S')) ++b[j].softClipCnt;
                //         else if (softClip[i][l]=="*") ++b[j].noMapCnt;
                //         else ++b[j].noSubsCnt;                   
                //     }
                // }

                // else if (readLen[i][l].length()==19){
                //      if(readHead[i][l]==id[j]){
                //         ++c[j].totalReadCnt;
                //         if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                //             ++c[j].misMapCnt;
                //             ++n;
                //         }
                //         else if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                //         strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++c[j].subsCnt;                      
                //         else if (strchr(softClip[i][l].c_str(), 'S')) ++c[j].softClipCnt;
                //         else if (softClip[i][l]=="*") ++c[j].noMapCnt;
                //         else ++c[j].noSubsCnt;                   
                //     }
                // }

                // else if (readLen[i][l].length()==20){
                //      if(readHead[i][l]==id[j]){
                //         ++d[j].totalReadCnt;
                //         if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                //             ++d[j].misMapCnt;
                //             ++n;
                //         }
                //         else if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                //         strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++d[j].subsCnt;                      
                //         else if (strchr(softClip[i][l].c_str(), 'S')) ++d[j].softClipCnt;
                //         else if (softClip[i][l]=="*") ++d[j].noMapCnt;
                //         else ++d[j].noSubsCnt;                   
                //     }
                // }

                // else if (readLen[i][l].length()==21){
                //      if(readHead[i][l]==id[j]){
                //         ++e[j].totalReadCnt;
                //         if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                //             ++e[j].misMapCnt;
                //             ++n;
                //         }
                //         else if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                //         strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++e[j].subsCnt;                      
                //         else if (strchr(softClip[i][l].c_str(), 'S')) ++e[j].softClipCnt;
                //         else if (softClip[i][l]=="*") ++e[j].noMapCnt;
                //         else ++e[j].noSubsCnt;                   
                //     }
                // }

                // else if (readLen[i][l].length()==22){
                //      if(readHead[i][l]==id[j]){
                //         ++f[j].totalReadCnt;
                //         if (i==lineIdenFirst[n]&&l==lineIdenSec[n]){
                //             ++f[j].misMapCnt;
                //             ++n;
                //         }
                //         else if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                //         strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++f[j].subsCnt;                      
                //         else if (strchr(softClip[i][l].c_str(), 'S')) ++f[j].softClipCnt;
                //         else if (softClip[i][l]=="*") ++f[j].noMapCnt;
                //         else ++f[j].noSubsCnt;                   
                //     }
                // }

            }
            // cout<<endl;
            ++j;
        }  

        // cout<<a[1].totalReadCnt<<" "<<b[1].totalReadCnt<<" "<<c[1].totalReadCnt<<" "<<d[1].totalReadCnt<<" "<<e[1].totalReadCnt<<" "<<f[1].totalReadCnt;
        // for (i=0; i<totalRef; i++){
        //     for (j=0; j<30; j++){
        //         cout<<subsLine[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }

        for (i=0; i<totalRef; i++){
            cout<<header[i]<<endl;
            // cout<<;
            cout<<"\t\t17\t18\t19\t20\t21\t22\t17\t18\t19\t20\t21\t22\t"<<endl;
            cout<<"TotalRead\t"<<a[i].totalReadRng<<"\t"<<b[i].totalReadRng<<"\t"<<c[i].totalReadRng<<"\t"<<d[i].totalReadRng<<"\t"<<e[i].totalReadRng<<"\t"<<f[i].totalReadRng<<"\t";
            cout<<a[i].totalReadCnt<<"\t"<<b[i].totalReadCnt<<"\t"<<c[i].totalReadCnt<<"\t"<<d[i].totalReadCnt<<"\t"<<e[i].totalReadCnt<<"\t"<<f[i].totalReadCnt<<endl;
            cout<<"NoSubsRead\t"<<a[i].noSubs<<"\t"<<b[i].noSubs<<"\t"<<c[i].noSubs<<"\t"<<d[i].noSubs<<"\t"<<e[i].noSubs<<"\t"<<f[i].noSubs<<"\t";
            cout<<a[i].noSubs<<"\t"<<b[i].noSubs<<"\t"<<c[i].noSubs<<"\t"<<d[i].noSubs<<"\t"<<e[i].noSubs<<"\t"<<f[i].noSubs<<endl;
            cout<<"softClip\t*\t*\t*\t*\t*\t*\t";
            cout<<a[i].softClipCnt<<"\t"<<b[i].softClipCnt<<"\t"<<c[i].softClipCnt<<"\t"<<d[i].softClipCnt<<"\t"<<e[i].softClipCnt<<"\t"<<f[i].softClipCnt<<endl;
            cout<<"correctMap\t*\t*\t*\t*\t*\t*\t";
            cout<<a[i].trueMapCnt<<"\t"<<b[i].trueMapCnt<<"\t"<<c[i].trueMapCnt<<"\t"<<d[i].trueMapCnt<<"\t"<<e[i].trueMapCnt<<"\t"<<f[i].trueMapCnt<<endl;
            cout<<"misMap\t\t*\t*\t*\t*\t*\t*\t";
            cout<<a[i].misMapCnt<<"\t"<<b[i].misMapCnt<<"\t"<<c[i].misMapCnt<<"\t"<<d[i].misMapCnt<<"\t"<<e[i].misMapCnt<<"\t"<<f[i].misMapCnt<<endl;
            cout<<"notMap\t\t*\t*\t*\t*\t*\t*\t";
            cout<<a[i].noMapCnt<<"\t"<<b[i].noMapCnt<<"\t"<<c[i].noMapCnt<<"\t"<<d[i].noMapCnt<<"\t"<<e[i].noMapCnt<<"\t"<<f[i].noMapCnt<<endl;

            cout<<"SubsRead\t"<<a[i].subs<<"\t"<<b[i].subs<<"\t"<<c[i].subs<<"\t"<<d[i].subs<<"\t"<<e[i].subs<<"\t"<<f[i].subs<<"\t";
            cout<<a[i].subs<<"\t"<<b[i].subs<<"\t"<<c[i].subs<<"\t"<<d[i].subs<<"\t"<<e[i].subs<<"\t"<<f[i].subs<<endl;
            cout<<"softClip\t*\t*\t*\t*\t*\t*\t";
            cout<<a[i].softClipCntSubs<<"\t"<<b[i].softClipCntSubs<<"\t"<<c[i].softClipCntSubs<<"\t"<<d[i].softClipCntSubs<<"\t"<<e[i].softClipCntSubs<<"\t"<<f[i].softClipCntSubs<<endl;
            cout<<"correctMap\t*\t*\t*\t*\t*\t*\t";
            cout<<a[i].trueMapCntSubs<<"\t"<<b[i].trueMapCntSubs<<"\t"<<c[i].trueMapCntSubs<<"\t"<<d[i].trueMapCntSubs<<"\t"<<e[i].trueMapCntSubs<<"\t"<<f[i].trueMapCntSubs<<endl;
            cout<<"misMap\t\t*\t*\t*\t*\t*\t*\t";
            cout<<a[i].misMapCntSubs<<"\t"<<b[i].misMapCntSubs<<"\t"<<c[i].misMapCntSubs<<"\t"<<d[i].misMapCntSubs<<"\t"<<e[i].misMapCntSubs<<"\t"<<f[i].misMapCntSubs<<endl;
            cout<<"notMap\t\t*\t*\t*\t*\t*\t*\t";
            cout<<a[i].noMapCntSubs<<"\t"<<b[i].noMapCntSubs<<"\t"<<c[i].noMapCntSubs<<"\t"<<d[i].noMapCntSubs<<"\t"<<e[i].noMapCntSubs<<"\t"<<f[i].noMapCntSubs<<endl;

            // cout<<a[i].softClipCnt<<"\t"<<b[i].softClipCnt<<"\t"<<c[i].softClipCnt<<"\t"<<d[i].softClipCnt<<"\t"<<e[i].softClipCnt<<"\t"<<f[i].softClipCnt<<endl;
            // // cout<<a[i].noSubsCnt<<"\t"<<b[i].noSubsCnt<<"\t"<<c[i].noSubsCnt<<"\t"<<d[i].noSubsCnt<<"\t"<<e[i].noSubsCnt<<"\t"<<f[i].noSubsCnt<<endl;
            // cout<<"SubsRead\t"<<a[i].subs<<"\t"<<b[i].subs<<"\t"<<c[i].subs<<"\t"<<d[i].subs<<"\t"<<e[i].subs<<"\t"<<f[i].subs<<"\t";
            // cout<<a[i].subsCnt+a[i].softClipCnt<<"\t"<<b[i].subsCnt+b[i].softClipCnt<<"\t"<<c[i].subsCnt+c[i].softClipCnt<<"\t"<<d[i].subsCnt+d[i].softClipCnt<<"\t"<<e[i].subsCnt+e[i].softClipCnt<<"\t"<<f[i].subsCnt+f[i].softClipCnt<<endl;
            
            // cout<<a[i].noMapCnt<<"\t"<<b[i].noMapCnt<<"\t"<<c[i].noMapCnt<<"\t"<<d[i].noMapCnt<<"\t"<<e[i].noMapCnt<<"\t"<<f[i].noMapCnt<<endl;   
            // cout<<"MisMap\t\t*\t*\t*\t*\t*\t*\t";        
            // cout<<a[i].misMapCnt<<"\t"<<b[i].misMapCnt<<"\t"<<c[i].misMapCnt<<"\t"<<d[i].misMapCnt<<"\t"<<e[i].misMapCnt<<"\t"<<f[i].misMapCnt<<endl<<endl;
        }  

    // for (i=0; i<totalRef; i++){
    //     cout<<header[i]<<endl<<"--------------------"<<endl;
    //     cout<<"Total Read:\t"<<totalRead[i]<<"\t|Total Read:\t\t"<<totalReadCnt[i]<<"\t|"<<endl;
    //     cout<<"No Subs Read:\t"<<noSubsMap[i]<<"\t|No Subs Read Mapped:\t"<<noSubsCnt[i]<<"\t|"<<endl;
    //     cout<<"Subs Read:\t"<<subsMap[i]<<"\t|SoftClip:\t\t"<<softClipCnt[i]<<"\t|"<<endl;
    //     cout<<"\t\t\t|Subs Read Mapped:\t"<<softClipCnt[i]+subsCnt[i]<<"\t|"<<endl;
    //     cout<<"Num Subs:\t"<<subsBaseNum[i]<<"\t|read not mapped:\t"<<noMapCnt[i]<<"\t|"<<endl;
    //     cout<<"\t\t\t|incorrect mapped:\t"<<misMapCnt[i]<<"\t|"<<endl<<endl;
    // }

        // for (i=0; i< totalRef; i++){
        // cout<<a[i].totalReadRng<<"\t"<<b[i].totalReadRng<<"\t"<<c[i].totalReadRng<<"\t"<<d[i].totalReadRng<<"\t"<<e[i].totalReadRng<<"\t"<<f[i].totalReadRng<<endl;
        // cout<<a[i].noSubs<<"\t"<<b[i].noSubs<<"\t"<<c[i].noSubs<<"\t"<<d[i].noSubs<<"\t"<<e[i].noSubs<<"\t"<<f[i].noSubs<<endl;
        // cout<<a[i].subs<<"\t"<<b[i].subs<<"\t"<<c[i].subs<<"\t"<<d[i].subs<<"\t"<<e[i].subs<<"\t"<<f[i].subs<<endl<<endl;
        // }
        return 0;
}