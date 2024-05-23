#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>	// remove()
using namespace std;

class Playfair {
	char mTable[25];
	string mPair;
	string mKey;
public:
	Playfair(string mKey, string mPair);
	void makeTable();
	void showTable();
	string makeEncryption(string mEncryption);
};

Playfair::Playfair(string mKey, string mPair) {
	this->mKey = mKey;
	this->mPair = mPair;
}

void Playfair::makeTable() {	// mKey와 mPair를 이용하여 mTable을 만드세요. (5 X 5 로 표현하시오)
	string alph = "abcdefghijklmnopqrstuvwxyz";
	int i, key_Check=0, alph_Check=0;

	// 사용자에게 입력 받은 mKey와 mPair 출력
	cout << "mKey : " << mKey << endl;
	cout << "mPair : " << mPair << endl;
	cout << endl;

	// 중복된 문자를 제거하여 유효한 mKey 생성
	for (i = 0; i < mKey.length(); i++)
		mKey.erase(remove(mKey.begin()+(i+1), mKey.end(), mKey[i]), mKey.end());

	// mPair의 세 번째 문자를 mPair의 첫 번째 문자로 변경하여 mKey 유효성 확인
	for (i = 0; i < mKey.length(); i++) {
		if (mKey[i] == mPair[2])
			mKey[i] = mPair[0];
	}

	// mKey에 없는 알파벳을 mKey의 뒤에 추가하여 알파벳 순서 정렬
	for (i = 0; i < mKey.length(); i++)
		alph.erase(remove(alph.begin(), alph.end(), mKey[i]), alph.end());

	// mPair의 세 번째 문자를 알파벳에서 제외하여 알파벳 순서 정렬
	alph.erase(remove(alph.begin(), alph.end(), mPair[2]), alph.end());

	// mKey와 알파벳을 결합하여 암호 테이블 생성
	string mtable = mKey + alph;
	strcpy(mTable, mtable.c_str());	// 문자열을 문자 배열로 변환
}

void Playfair::showTable() {	// mTable에 있는 값들을 5 X 5 로 화면에 출력하시오.
	int i, j;
	cout << "---TABLE---" << endl;
	for (i = 0; i < 5; i++) {
		cout << " ";
		for (j = 0 + 5 * i; j < 5 + 5 * i; j++) {
			cout << mTable[j] << " ";
		}
		cout << endl;
	}
	cout << "-----------" << endl;
	cout << endl;
}

string Playfair::makeEncryption(string mEncryption) {
	string sen_encryption = "";
	int i, j, check = 0;

	cout << "원    문 : " << mEncryption << endl;

	// 공백 제거
	mEncryption.erase(remove(mEncryption.begin(), mEncryption.end(), ' '), mEncryption.end());

	// 소문자로 변경
	for (i = 0; i < mEncryption.length(); i++)
		mEncryption[i] = tolower(mEncryption[i]);

	//원문에 mPair 두번째 글자가 있으면 첫번째 글자로 변경
	for (i = 0; i < mEncryption.length(); i++) {
		if (mEncryption[i] == mPair[2])
			mEncryption[i] = mPair[0];
	}

	// 두 문자가 같을 경우 사이에 x 추가
	for (i = 0; i < (mEncryption.length() - 1); i += 2) {
		if (mEncryption[i] == mEncryption[i + 1]) {
			mEncryption.insert(i+1, "x");
		}
	}

	// 글자수가 홀수인 경우 끝에 x 추가
	if (mEncryption.length() % 2 == 1) {
		mEncryption.append("x");
	}
	cout << "x 삽입문 : " << mEncryption << endl;

	int row1, row2;
	int column1, column2;
	int first_word, second_word;
	int AbsCol, AbsRow;
	int k, t;

	for (k = 0; k < mEncryption.length(); k += 2) {		// 두문자씩 검사
		for (t = 0; t < 5; t++) {			// t는 행 표현
			for (i = 5 * t; i < (5 + 5 * t); i++) {	// i는 첫번째 문자의 열
				if (mEncryption[k] == mTable[i]) {
					column1 = i;
					row1 = t;
					break;
				}
			}
			for (j = 5 * t; j < (5 + 5 * t); j++) {	// j는 두번째 문자의 열
				if (mEncryption[k + 1] == mTable[j]) {
					column2 = j;
					row2 = t;
					break;
				}
			}
		}

		AbsCol = abs(column1 – column2); //2번 경우에서 else if 사용하기 위해 미리 초기화

		//1. 행이 같은 경우 - 오른쪽에 있는 문자로 대체
		if (row1 == row2) {
			t = row1;
			if (column1 == (4 + 5 * t)) 
				first_word = column1 - 4; //맨 오른쪽 문자인 경우에 같은 행 맨 왼쪾 문자로 대체
			else 
				first_word = column1 + 1;						
			if (column2 == (4 + 5 * t)) 
				second_word = column2 - 4;
			else 
				second_word = column2 + 1;
			sen_encryption += mTable[first_word];
			sen_encryption += mTable[second_word];
		}

		//2. 열이 같은 경우 - 아래쪽에 있는 문자로 대체
		else if (AbsCol % 5 == 0) {
			if (column1 >= 20) 
				first_word = column1 - 20;		//맨 아래쪽 문자인 경우에 같은 열 맨 위의 문자로 대체
			else 
				first_word = column1 + 5;					
			if (column2 >= 20) 
				second_word = column2 - 20;	
			else 
				second_word = column2 + 5;
			sen_encryption += mTable[first_word];
			sen_encryption += mTable[second_word];
		}

	      //3. 행과 열 둘다 다를 경우 - 각각 행과 열이 만나는 곳에 위치한 문자로 대체
		else {
			AbsRow = abs(row1 - row2);
			if (row1 < row2) {
				first_word = column2 - 5 * AbsRow;						//두 단어와의 열 차이만큼 곱해서 해당 문자로 대체
				second_word = column1 + 5 * AbsRow;		
			}
			else {
				first_word = column2 + 5 * AbsRow;
				second_word = column1 - 5 * AbsRow;
			}
			sen_encryption += mTable[first_word];
			sen_encryption += mTable[second_word];
		}
	}

	cout << "암호화문 : " << sen_encryption << endl;
	return sen_encryption;
}

int main() {
	Playfair pfair("goodjob", "o/y");
	pfair.makeTable();
	pfair.showTable();
	pfair.makeEncryption("yo");
}
