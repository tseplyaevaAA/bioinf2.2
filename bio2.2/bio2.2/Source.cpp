#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int amount_str(string abc) {
	int res = 0;
	string s;
	ifstream fin(abc, ios_base::in);
	if (fin.is_open()) while (getline(fin, s)) res++;
	else return 0;
	fin.close();
	return res;
}

char getletter(int n)
{
	if (n == 0) return 'a';
	if (n == 1) return 'c';
	if (n == 2) return 'g';
	if (n == 3) return 't';
}

int ham_distance(string s1, string s2) {
	int result = 0;
	for (int i = 0; i < s1.length(); i++)
		if (s1[i] != s2[i]) result++;
	return result;
}

int  total_distance(string* dna, string abc, int t) {

	int result = 0;
	int min = abc.length() + 1;

	for (int i = 0; i < t; i++) {
		for (int j = 0; j < dna[0].length() - abc.length() + 1; j++) {
			if (ham_distance(abc, dna[i].substr(j, abc.length())) < min) {
				min = ham_distance(abc,dna[i].substr(j, abc.length()));
			}
		}
		result += min;
		min = abc.length() + 1;
	}
	return result;
}

string search_median(string* dna, int t, int l, int n){

	int totdist = 1000000000;
	string answer = "";
	string  consensus = "";

	int i = 0;
	while (i < l) {
		consensus += 'a';
		i++;
	}

	//lmers
	int *ind = new int[l];
	for (int i = 0; i < t; i++) ind[i] = 0;
	string word = "";
	int c = pow(4, l); //diff positions

	for (int i = 0; i < c; i++) {
		for (int j = 0; j < l; j++) {
			word += getletter(ind[j]);
		}

		if (total_distance(dna, word, t) < totdist) {
			totdist = total_distance(dna, word, t);
			consensus = word;
		}
		word = "";

		//new iteration
		for (int j = 0; j < l; j++) {
			ind[j]++;
			if (ind[j] < 4)
				break;
			ind[j] = 0;
		}
	}

	answer = consensus;
	return answer;
}



int main(){

		string info;
		string *dna;
		int *a = new int[2];
		ifstream input("input.txt", ios_base::in);
		getline(input, info);
		int l = stoi(info);
		a[1] = amount_str("input.txt");
		dna = new string[a[1]];
		string answer1 = "";
		int i = 0;
		input.seekg(0, ios::cur);

		while (getline(input, dna[i])){
			i++;
			if (i == a[1]){ break; }
		}

		/*for (int i = 0; i < a[1]; i++){
			cout << dna[i] << endl;
		}*/

		int n = dna[1].size();
		int j = 0;

		answer1 = search_median(dna,a[1]-1, l, n);

		ofstream new_file1("output.txt");
		new_file1 << answer1 <<endl;
		new_file1.close();
		delete[] a;
	return 0;
}