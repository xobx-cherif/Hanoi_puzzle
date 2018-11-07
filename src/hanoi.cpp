// Hanoei : By Bilel CHERIF 
// A C++ program to solve the tower oh hanoei puzzle

#include<iostream>
#include<ctime>
#include<exception>
#include <limits>

using namespace std;

class Piece{

	int pieceID;
 	char *w;

	public:
	Piece(int ID, char* who){
		w = who;
		pieceID=ID;
	}
	Piece(){
		pieceID=0;
	}
	int getID(){
		return pieceID;
	}

	char* who(){

		return w;
	}
	void setWho(char* who){

		w=who;
	}
	void setID(int n){
	
		pieceID=n;
	}
};

struct elem {
		char * who;
		Piece p[64];

	};

class Toh {
	int n, mv;

	public:

	elem initial={"initial"}, target={"target"}, auxiliary={"auxiliary"};

	Toh(int num){
		n=num;

		for(int i=0 ; i<n; i++){
			initial.p[i]= *(new Piece(i+1, "initial"));
		}
		
		cout<<"Toh initialized succecefully with "<<n<<" elements in initial bar."<<endl;
	}
	int getMv(){

		return mv;
	}

	void solve(elem *A , elem *B , elem *C , int n){

			if(n > 0){

				solve(A,C,B, n-1);

				int z;
				int y;

				z=0;
				y=0;

				while(A->p[z].getID() != 0){
					z++;
				}

				while(B->p[y].getID() !=0 ){
					y++;
				}

				//cout<<"z = "<<z<<" y = "<<y<<" id: "<<A->p[z].getID() <<endl;
				
				B->p[y] = *(new Piece(A->p[z-1].getID(), B->who));
				A->p[z-1].setID(0);
				cout<<"Move 1 disk with ID: "<< B->p[y].getID() <<" from "<< A->who<<" to "<<B->who <<endl;
				mv++;
				solve(C,B,A, n-1);
	
			}
	}

};

int main(){
	rec:
	int n=0;

	cout<<"enter the number of your TOH pieces: "<<endl;
	try{
		if(!(cin>>n)) {

			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(),'\n');
			throw "not int";
			}
	}catch(const char *e){
		cout<<"You should give me an integer! Let's try again"<<endl;
		cin.clear();
		goto rec;
	}
	cout<<"You selected "<<n<<" pieces."<<endl<<"Initializing your toh"<<endl;
	Toh toh(n);
	int i=0;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"Initializing the game"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	while (toh.initial.p[i].getID() != 0 ){
		cout<< "Piece "<<i<<" ID is: "<< toh.initial.p[i].getID()<<endl;
		cout<<toh.initial.p[i].who()<<endl;
		i++;
	}

	cout<<"----------------------------------------------------"<<endl;
	cout<<"Before solve"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	for (i=0; i<n; i++){
		cout<<toh.initial.p[i].who()<<": "<<toh.initial.p[i].getID()<<endl; 
	}
	cout<<"----------------------------------------------------"<<endl;
	cout<<"Solving the game"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	
	int start_s=clock();
	toh.solve(&toh.initial,&toh.target,&toh.auxiliary, n);
	start_s-=clock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"After solve"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	for (i=0; i<n; i++){
		cout<<toh.initial.p[i].who()<<": "<<toh.initial.p[i].getID()<<endl; 
	}
	for (i=0; i<n; i++){
		cout<<toh.target.p[i].who()<<": "<<toh.target.p[i].getID()<<endl; 
	}
	cout<<"----------------------------------------------------"<<endl;

	cout<<endl<<"Now let's see some stats maybe the world will end"<<endl;
	cout<<"as it says the myth !!"<<endl<<endl;
	cout<<"-----------------------------------------"<<endl;
	cout<<"n pieces"<<"	"<<"n mooves"<<"	"<<"duration"<<endl;
	cout<<"-----------------------------------------"<<endl;
	cout<<n<<"		"<<toh.getMv()<<"	  	"<<-start_s/double(CLOCKS_PER_SEC)*1000<<endl;
	cout<<"-----------------------------------------"<<endl;
	cout<<endl<<"So we are making: "<<toh.getMv()/-(start_s/double(CLOCKS_PER_SEC)*1000)<<" moove/second"<<endl;
	return 0;

}
