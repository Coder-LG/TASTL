#pragma once
#include<iostream>
namespace TA {
	class string {
	private:



	public:
		string() {

		}
		string(const string& str) {

		}
		string(const char* str) {

		}
		~string() {

		}
		void clear() {

		}

		friend std::ostream& operator<<(std::ostream& out, const string& str) {

		}
		friend std::ostream& operator>>(std::ostream& in, const string& str) {

		}
		friend string& operator+(const string& str1, const string& str2) {
			string* temp = new string();
			return *temp;
		}
		char& operator[](const int& i) {

		}

		string& operator=(const string& str) {

		}
		string& operator=(const char* str) {

		}

		int length() const {

		}
		bool isempty() const {

		}
		int capacity() const {

		}
		char* c_str() {

		}
		string& substr() {

		}
		begin() {

		}
		end() {

		}
		rbegin() {

		}
		rend() {

		}
		find() {
		}
		substr() {

0.		}
	};
	/*
	+ =，append( )，push_back()	添加字符
	insert ()	插入字符
	erase()	删除字符
	replace()	替换字符
	==，！ =，<，<=，>，>=，compare()	比较字符串内容
0	substr()	返回子字符串*/
}