
#include <string>
#include <vector>
#include "strops.h"

std::string JoinArrayPieces(std::string input[])
{
	std::string outStr = "";
	for (int i = 0; i < sizeof(input) / sizeof(input[0]); i++)
	{
		outStr += input[i];
	}
	return outStr;
}

std::string JoinArrayPieces(std::vector<std::string> input)
{
	std::string outStr = "";
	for (int i = 0; i < input.size(); i++)
	{
		outStr += input[i];
	}
	return outStr;
}

std::string CommaLargeNumber(int num) {
	int v = num;
	auto s = std::to_string(v);

	int n = s.length() - 3;
	int end = (v >= 0) ? 0 : 1; // Support for negative numbers
	while (n > end) {
		s.insert(n, ",");
		n -= 3;
	}

	return s;
}

std::string CommaLargeNumber(float num) {
	int v = (int)num;
	auto s = std::to_string(v);

	int n = s.length() - 3;
	int end = (v >= 0) ? 0 : 1; // Support for negative numbers
	while (n > end) {
		s.insert(n, ",");
		n -= 3;
	}

	s += "." + SplitString(std::to_string(num), ".")[1];

	return s;
}

// Function to pad the front of a string with a character to make it a certain length
std::string PadString(const std::string& input, char padChar, size_t desiredLength) {
	std::string result = input;
	while (result.length() < desiredLength) {
		result.insert(result.begin(), padChar);
	}
	return result;
}

// Function to extract the padded characters from the front of a string until another character is found
std::string ExtractPaddedChars(const std::string& input, char padChar) {
	std::string result;
	size_t index = 0;

	// Extract the padded characters until a non-padded character is found
	while (index < input.length() && input[index] == padChar) {
		result += input[index];
		index++;
	}

	return result;
}

// Split a string <str> by a delimiter <delim>, and return a vector of strings
std::vector<std::string> SplitString(std::string str, std::string delim)
{
	std::vector<std::string> splittedString;
	int startIndex = 0;
	int  endIndex = 0;
	while ((endIndex = str.find(delim, startIndex)) < str.size())
	{
		std::string val = str.substr(startIndex, endIndex - startIndex);
		splittedString.push_back(val);
		startIndex = endIndex + delim.size();
	}
	if (startIndex < str.size())
	{
		std::string val = str.substr(startIndex);
		splittedString.push_back(val);
	}
	return splittedString;
}

// trim from start (in place)
void ltrim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
void rtrim(std::string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}
// Overrided by boost::trim
// trim from both ends (in place)
std::string TrimString(std::string s)
{
	std::string sN = s;
	ltrim(sN);
	rtrim(sN);
	return sN;
}

// Convert string to uppercase
std::string ToUpper(std::string s)
{
	std::string sN = s;
	for (auto& c : sN) c = toupper(c);
	return sN;
}

// Convert string to lowercase 
std::string ToLower(std::string s)
{
	std::string sN = s;
	for (auto& c : sN) c = tolower(c);
	return sN;
}

bool StringStartsWith(std::string str, std::string substr)
{
	for (int i = 0; i < substr.length(); i++)
	{
		if (str[i] != substr[i])
			return false;
	}
	return true;
}

char toHexChar(int value) {
	if (value < 10) {
		return static_cast<char>('0' + value);
	}
	else {
		return static_cast<char>('a' + value - 10);
	}
}

void stringToHex(char* input, char* output, int len) {
	for (int i = 0; i < len; i++)
	{
		output[0] = toHexChar((static_cast<unsigned char>(*input) >> 4) & 0x0F);
		output[1] = toHexChar(static_cast<unsigned char>(*input) & 0x0F);
		input++;
		output += 2;
	}
	*output = '\0'; // Add null terminator at the end
}

char d[30]; // Buffer for the CharStrStartsWith() function check
// Check if the unsigned char* <str> starts with another char* <substr>
bool CharStrStartsWith(unsigned char* str, char* substr, int len)
{
	char* c = d;
	//for (int i = 0; i < len; i++)
	//{
	//	sprintf(c + (i * 2), "%02x", str[i]);
	//}
	stringToHex((char*)str, c, len);
	for (int i = 0; i < len; i++)
	{
		if (c[i] != substr[i])
			return false;
	}
	return true;
}

// Function to compare two char* representing numbers
bool CompareCharNumbers(const unsigned char* number1, const unsigned char* number2) {
	//// Skip leading zeros
	//while (*number1 == '0' && *(number1 + 1) != '\0') {
	//	number1++;
	//}
	//while (*number2 == '0' && *(number2 + 1) != '\0') {
	//	number2++;
	//}

	int it = 0;
	// Compare the remaining digits
	while (it < 32) {
		if (*number1 < *number2) {
			return false;
		}
		else if (*number1 > *number2) {
			return true;
		}
		number1++;
		number2++;
		it++;
	}

	// If one number has more digits, the shorter one is considered smaller
	return *number1 == '\0' && *number2 != '\0';
}

// Replace all instances of the escape symbol '\n' with the string "\\n"
std::string ReplaceEscapeSymbols(std::string s)
{
	std::string out = "";
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '\n')
			out += "\\n";
		else
			out += s[i];
	}
	return out;
}
