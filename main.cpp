#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

int main(){
    ifstream infile1, infile2, infile3;
    ofstream outfile;
    int totalRef=0, i=0, j=0, k=0, l=0, m=0;
    string in1="expected_hsa.txt", in2="output_hsa.sam", out="result.txt", line, lineTemp, lineIden;
    bool newObj;

    infile1.open(in1.c_str());
        while(getline(infile1, line)){
            if(line[0]=='@') ++totalRef;
        }

    string header[totalRef], totalRead[totalRef], noSubsMap[totalRef], subsMap[totalRef], subsBaseNum[totalRef];
    std::string::size_type sz;
    int totalReadCnt[totalRef], noSubsCnt[totalRef], subsCnt[totalRef], softClipCnt[totalRef], noMapCnt[totalRef], misMapCnt[totalRef];

    infile2.open(in1.c_str());
        while(getline(infile2, line)){
            if(line[0]=='@'){
                line.erase(find(line.begin(), line.end(), '@'));
                header[i]=line;
            }
            else if (line[0]=='\0'){}
            else{  
                k=0;
                for (j=0; j<line.length(); j++){
                    if (line[j]=='+')++k;
                    else {
                        if (k==0) totalRead[i]+=line[j];
                        else if (k==1) noSubsMap[i]+=line[j];
                        else if (k==2) subsMap[i]+=line[j];
                        else if (k==3) subsBaseNum[i]+=line[j];
                        else break;
                    }
                    // cout<<k<<" ";
                }
                ++i;
            }
        }
        int totSamLine=100;
        string readHead[totalRef][totSamLine], seqHead[totalRef][totSamLine], softClip[totalRef][totSamLine], subsDet[totalRef][totSamLine];  
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
                                else if (k==2) seqHead[i][l]+=line[j];
                                else if (k==5) softClip[i][l]+=line[j];
                                else if (k==15) subsDet[i][l]+=line[j];
                            }
                        }
                        ++l;
            }
        }
                // for (i=0; i<totalRef; i++){
                //     for(int l=0; l<totSamLine; l++){
                //         cout<<readHead[i][l]<<"\t"<<seqHead[i][l]<<"\t"<<softClip[i][l]<<"\t"<<subsDet[i][l]<<endl;
                //     }
                //     cout<<endl;
                // }
        
            // for(i=0; i<totSamLine; i++){
            //     if (readHead[i]=="") break;
            //     cout<<readHead[i]<<"\t"<<seqHead[i]<<"\t"<<softClip[i]<<"\t"<<subsDet[i]<<endl;
            // }
        infile3.close();
    
    // for (i=0; i<totalRef; i++){cout<<i<<"\t"<<softClip[i][3]<<endl;}
//-----------------------------------------------------------------------------------------------------------------------------
        j=0;
        for (i=0; i<totalRef; i++){
            for (int l=0; l<totSamLine; l++){
                // cout<<i<<"\t"<<l<<endl;
                // cout<<readHead[i][l]<<endl;

                    if(readHead[i][l]==header[j]){
                        ++totalReadCnt[j];
                        if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                        strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++subsCnt[j];                      
                        else if (strchr(softClip[i][l].c_str(), 'S')) ++softClipCnt[j];
                        else if (softClip[i][l]=="*") ++noMapCnt[j];
                        else ++noSubsCnt[j];                   
                    }
                    else ++misMapCnt[j];
                
                // if (l>0){
                //     if (readHead[i][l]==readHead[i][l-1]){
                //         // cout<<
                //         if(readHead[i][l]==header[j]){
                //             ++totalReadCnt[j];
                //             if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                //             strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++subsCnt[j];                      
                //             else if (strchr(softClip[i][l].c_str(), 'S')) ++softClipCnt[j];
                //             else ++noSubsCnt[j];                             
                //         }
                //         else ++misMapCnt[j];
                //     }
                //     else{
                //         if (totalReadCnt[j]!=stoi(totalRead[j])) noMapCnt[j]=stoi(totalRead[j])-totalReadCnt[j];
                //         ++j;
                        
                //         if(readHead[i][l]==header[j]){
                //             ++totalReadCnt[j];
                //             if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                //             strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++subsCnt[j];
                //             else ++noSubsCnt[j];                           
                //             if (strchr(softClip[i][l].c_str(), 'S')) ++softClipCnt[j];
                //         }
                //         else ++misMapCnt[j];
                //     }   

                // }
                // else {
                //         if(readHead[i][l]==header[j]){
                //             ++totalReadCnt[j];
                //             if (strchr(subsDet[i][l].c_str(), 'A')||strchr(subsDet[i][l].c_str(), 'T')||strchr(subsDet[i][l].c_str(), 'G')||
                //             strchr(subsDet[i][l].c_str(), 'C')||strchr(subsDet[i][l].c_str(), 'N')) ++subsCnt[j];
                //             else ++noSubsCnt[j];                           
                //             if (strchr(softClip[i][l].c_str(), 'S')) ++softClipCnt[j];
                //         }
                //         else ++misMapCnt[j];
                // }
                // // cout<<i<<","<<l<<"\t";
                // if (readHead[i][l]==""){ cout<<"BREAK";break;}
                // // cout<<totalReadCnt[j]<<"\t"<<noSubsCnt[j]<<"\t"<<subsCnt[j]<<"\t"<<softClipCnt[j]<<"\t"<<noMapCnt[j]<<"\t"<<misMapCnt[j]<<endl; 
                // // cout<<readHead[i]<<"  "<<header[j]<<endl;
            }
            // cout<<endl;
            ++j;
        }    

    for (i=0; i<totalRef; i++){
        cout<<header[i]<<endl<<"--------------------"<<endl;
        cout<<"Total Read:\t"<<totalRead[i]<<"\t|Total Read:\t\t"<<totalReadCnt[i]<<"\t|"<<endl;
        cout<<"No Subs Read:\t"<<noSubsMap[i]<<"\t|No Subs Read Mapped:\t"<<noSubsCnt[i]<<"\t|"<<endl;
        cout<<"Subs Read:\t"<<subsMap[i]<<"\t|SoftClip:\t\t"<<softClipCnt[i]<<"\t|"<<endl;
        cout<<"\t\t\t|Subs Read Mapped:\t"<<softClipCnt[i]+subsCnt[i]<<"\t|"<<endl;
        cout<<"Num Subs:\t"<<subsBaseNum[i]<<"\t|read not mapped:\t"<<noMapCnt[i]<<"\t|"<<endl;
        cout<<"\t\t\t|incorrect mapped:\t"<<misMapCnt[i]<<"\t|"<<endl<<endl;
    }
        return 0;
}