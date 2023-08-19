#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;

void generate(int matrix_size, int orient, string word){
    string origWord;
    origWord.assign(word);
    for (int it = 0; it<int(origWord.length());it++){
        origWord[it] = toupper(origWord[it]);
    }

    word.append(".txt");
    
    string path = "testCases/" + word;

    fstream file;
    file.open(path, ios::out);
    if(!file){
        cout<<"failed operation"<<endl;
        return;
    }

    string line;
    char randchar;
    int rand1 = rand()%(matrix_size - 10);
    int rand2 = rand()%(matrix_size - 10);

    cout<<rand1<<endl;
    cout<<rand2<<endl;

    switch (orient){
        case 0:{ 
            file<<"vertical"<<endl;
            int strIt = 0;
            for (int i = 0; i<matrix_size;i++){
                for (int j = 0;j<matrix_size;j++){
                    if(i == rand1 && j == rand2 && (strIt < int(origWord.length()))){
                        line.push_back(origWord[strIt]);
                        line.push_back(' ');
                        j++;
                        rand1++;
                        strIt++;
                    }
                    randchar = 'A' + rand()%26;
                    line.push_back(randchar);
                    line.push_back(' ');
                }
                file<<line<<endl;
                line.clear();
            }
            
            break;}
        
        case 1:{ 
            file<<"horizontal"<<endl;
            for (int i = 0; i<matrix_size;i++){
                for (int j = 0;j<matrix_size;j++){
                    if (i == rand1 && j == rand2){
                        for(int k = 0; k<int(origWord.length());k++){
                            line.push_back(origWord[k]);
                            line.push_back(' ');
                        }
                        j = j + origWord.length();
                    }
                    randchar = 'A' + rand()%26;
                    line.push_back(randchar);
                    line.push_back(' ');
                }
            //cout<<line<<endl;
            file<<line<<endl;
            line.clear();
            }
            break;}
    }
    file.close();
    return;

}


int main(){
    int cant_files;
    int matrix_size;
    int orient;

    cout<<"cantidad archivos: ";cin>>cant_files; 
    cout<<"tamano matriz: ";cin>>matrix_size;

    cout<<"orientacion: ";cin>>orient; //orientacion 0 para vertical, 1 para horizontal

    string word;

    for (int i = 0; i < cant_files; i++){
        cout<<"ingrese palabra a ocultar: "; cin>>word;
        generate(matrix_size, orient, word);

    }
    return 0;
}