#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define ll long long
using namespace std;

typedef pair <char,char> token;
struct sequence{
	vector <token> tokSequence;
	int valSequence,lenSequence;
};

struct result{
	int valRes,lenRes;
	vector <token> tokRes;
	vector <pair <int,int> > posRes;
};

short int tipeInp;
string strinp,ans;
result curRes,finalRes;
int buffer, nSequence, row, col;
double execTime;
vector <vector <token> > dataToken;
vector <vector <bool> > visToken;
vector <sequence> dataSequence;

token stringToToken(string s){
	token res;
	if(s.length()!=2){
		cout<<"Masukan token tidak valid, program diberhentikan";
		exit(0);
	}
	res.first = s[0];
	res.second = s[1];
	return res;
}

void finalResToOp(){
	ans+="Result:\n";
	ans+=to_string(finalRes.valRes);
	ans+="\n";
	for(int i=0;i<finalRes.lenRes;i++){
		ans+=finalRes.tokRes[i].first;
		ans+=finalRes.tokRes[i].second;
		if(i!=finalRes.lenRes-1) ans+=" ";
		else ans+="\n";
	}
	for(int i=0;i<finalRes.lenRes;i++){
		ans+=to_string(finalRes.posRes[i].second+1);
		ans+=", ";
		ans+=to_string(finalRes.posRes[i].first+1);
		ans+="\n";
	}
	ans+="\n";
	ans+=to_string(execTime);
	ans+=" ms\n";
}

void separateToken(string s,int idx){
	stringstream full(s);
	string word;
	dataSequence[idx].lenSequence=0;
	while(full>>word){
		dataSequence[idx].lenSequence++;
		dataSequence[idx].tokSequence.push_back(stringToToken(word));
	}
}

void getInpType(){
	tipeInp = -1;
	while(tipeInp == -1){
		cout<<"Pilih Tipe Masukan: \n 1.File txt \n 2.Command Line"<<endl;
		cin>>strinp;
		if(strinp == "1")tipeInp = 1;
		else{
			if(strinp == "2")tipeInp = 2;
			else{
				cout<<"Tipe masukan tidak valid silahkan masukkan kembali tipe masukan"<<endl;
			}
		}
	}
}

void displayToken(){
	ans+= "Dihasilkan Matriks:\n";
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			ans+=dataToken[i][j].first;
			ans+=dataToken[i][j].second;
			if(j!=row-1) ans+=" ";
			else ans+="\n";
		}
	}
	ans+="\n";
}

void displaySequence(){
	ans+= "Dihasilkan ";
	ans+= to_string(nSequence);
	ans+= " Sequence:\n";
	for(int i=0;i<nSequence;i++){
		for(int j=0;j<dataSequence[i].lenSequence;j++){
			ans+=dataSequence[i].tokSequence[j].first;
			ans+=dataSequence[i].tokSequence[j].second;
			if(j!=dataSequence[i].lenSequence-1) ans+=" ";
			else ans+="\n";
		}
		ans+=to_string(dataSequence[i].valSequence);
		ans+="\n";
	}
	ans+="\n";
}

void type1(){
	cout<<"masukkan nama file yang ingin dibaca (tanpa menulis.txt): ";
	cin>>strinp;
	string p="test/input/";
	p+=strinp;
	p+=".txt";
	ifstream in(p);
	in>>buffer>>col>>row;
	dataToken.resize(row,vector<token> (col));
	visToken.resize(row,vector<bool> (col));
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			in>>strinp;
			dataToken[i][j]=stringToToken(strinp);
			visToken[i][j]=false;
		}
	}
	in>>nSequence;
	dataSequence.resize(nSequence);
	strinp="";
	for(int i=0;i<nSequence;i++){
		getline(in,strinp);
		getline(in,strinp);
		separateToken(strinp,i);
		in>>dataSequence[i].valSequence;
	}
}


void type2(){
	srand((int)time(0));
	int nUniqueToken, maxSequenceLen;
	//ambil jumlah dan data token unik
	cout<<"masukkan jumlah token unik: ";
	cin>>nUniqueToken;
	token jenisToken[nUniqueToken];
	cout<<"masukkan token unik: "<<endl;
	for(int i=0;i<nUniqueToken;i++){
		cin>>strinp;
		jenisToken[i]=stringToToken(strinp);
	}
	//ambil masukan lain
	cout<<"masukkan ukuran buffer: ";
	cin>>buffer;
	cout<<"masukkan ukuran matriks: ";
	cin>>col>>row;
	cout<<"masukkan jumlah sekuens: ";
	cin>>nSequence;
	cout<<"masukkan panjang maksimum sekuens: ";
	cin>>maxSequenceLen;
	//bentuk matriks
	dataToken.resize(row,vector<token> (col));
	visToken.resize(row,vector<bool> (col));
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			dataToken[i][j]=jenisToken[rand()%nUniqueToken];
			visToken[i][j]=false;
		}
	}
	//bentuk sequence
	dataSequence.resize(nSequence);
	for(int i=0;i<nSequence;i++){
		dataSequence[i].lenSequence = rand()%(maxSequenceLen-1)+1;
		for(int j=0;j<dataSequence[i].lenSequence;j++){
			dataSequence[i].tokSequence.push_back(jenisToken[rand()%nUniqueToken]);
		}
		dataSequence[i].valSequence=rand()%200-50;
	}
	cout<<endl;
}

bool checkExist(int idxSeq){
	for(int i=0;i<curRes.lenRes;i++){
		if(dataSequence[idxSeq].lenSequence>curRes.lenRes-i) return 0;
		else{
			for(int j=0;j<=dataSequence[idxSeq].lenSequence;j++){
				if(j==dataSequence[idxSeq].lenSequence) return 1;
				if(dataSequence[idxSeq].tokSequence[j]!=curRes.tokRes[i+j]) break;
			}
		}
	}
	return 0;
}

void calculatePoint(){
	curRes.valRes=0;
	for(int i=0;i<nSequence;i++){
		curRes.valRes+=(checkExist(i)*dataSequence[i].valSequence);
	}
	if(curRes.valRes>finalRes.valRes||(curRes.valRes==finalRes.valRes && curRes.lenRes<finalRes.lenRes)){
		finalRes=curRes;
	}
}

void generatePos(int posR, int posC,bool vertikal,int reBuff){
	if(reBuff==-1) return;
	visToken[posR][posC]=true;
	curRes.lenRes+=1;
	curRes.tokRes.push_back(dataToken[posR][posC]);
	curRes.posRes.push_back(make_pair(posR,posC));
	calculatePoint();
	if(vertikal){
		for(int i=0;i<row;i++){
			if(visToken[i][posC]==false){
				generatePos(i,posC,false,reBuff-1);
			}
		}
	}
	else{
		for(int i=0;i<col;i++){
			if(visToken[posR][i]==false){
				generatePos(posR,i,true,reBuff-1);
			}
		}
	}
	visToken[posR][posC]=false;
	curRes.lenRes-=1;
	curRes.tokRes.pop_back();
	curRes.posRes.pop_back();
}

int main (){
	//inisialisasi
	ans="";
	finalRes.valRes=0;
	finalRes.lenRes=0;
	curRes.valRes=0;
	curRes.lenRes=0;

	//mengambil masukan
	getInpType();
	if(tipeInp==2){
		type2();
		displayToken();
		displaySequence();
	}
	else{
		type1();
	}

	//menghitung poin maksimal
	auto start = chrono::high_resolution_clock::now();
	for(int i=0;i<col;i++){
		generatePos(0,i,true,buffer-1);
	}
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
	execTime = duration.count();
	finalResToOp();
	cout<<ans<<endl;
	cout<<"Apakah ingin menyimpan solusi? (y/n)";
	strinp="";
	while(strinp!="y"&&strinp!="n"){
		cin>>strinp;
		if(strinp!="y"&&strinp!="n"){
			cout<<"masukan tidak valid, silahkan ulangi"<<endl;
		}
	}
	if(strinp=="y"){
		cout<<"masukkan nama file tujuan: ";
		cin>>strinp;
		string p="test/output/";
		p+=strinp;
		p+=".txt";
		ofstream ofile(p);
		ofile<<ans;
		ofile.close();
	}
}
