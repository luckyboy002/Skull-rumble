#include<iostream>
#include<windows.h>
#include<stdio.h>
using namespace std;

int main(){
	
	system("COLOR 1a");
	system("cls");
	printf("\e[?251");
	
	SetConsoleCP(473);
	SetConsoleOutputCP(437);
	int bar1 = 177 , bar2 = 219;
	
	cout<<"\n\n\n\t\t\t\tLoading...";
	cout<<"\n\n\n\t\t\t\t";
	
	for(int i = 0; i < 25; i++)
		cout<<(char)bar1;
	
	
	cout<<"\r";
	cout<<"\t\t\t\t";
	for(int i = 0; i < 25; i++){
		cout<<(char)bar2;
		Sleep(150);
	}
	
	cout<<"\n\t\t\t\t"<<(char)1<<"!";
	system("pause");
	return 0;
}
