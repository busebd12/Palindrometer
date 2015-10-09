/*
Author: Brendan Busey
Date: 10/9/15
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

//function to read in file
//the keyword auto here means that the compiler figures out the return type of the function for us
auto readInFile(const string& FileName)
{
	vector<string> v;

	int input;

	ifstream file;

	file.open(FileName.c_str());

	string convertedValue;

	while(file >> convertedValue && convertedValue!="0")
	{
		v.emplace_back(convertedValue);
	}

	return v;
}

auto doPalindromeMeter(vector<string>& OdometerReadings)
{
	/*
	basic idea: 
	loop through the odometer times 
	convert each time to a string
	then, reverse the string and compare
	if they two are equal, we know we have a palindrome from the start and we just add it to the vector 
	if they are not equal, then we don't have a palindrome and we do the following (in a do-while loop):
		1) store length of current mileage reading since we will need it later
		2) convert the current mileage from string to int
		2) increment the miles by one
		3) convert the miles back to string
		4) find the length difference between the original mileage and the incremented mileage strings
		5) that difference tells you how many leading zeros to add to the front of the incremented mileage count
		6) compare the original mileage string and the incremented mileage string with the zeros added to the front
		4) if they are equal then we have a palindrome, and we add the two strings to the vector
		5) if they are not equal, we just go back to the top of the do-while loop and repeat steps 1-6 until we find a palindrome
		6) once we find a palindrome, we add the two strings to the vector
	After we have gone through all of the odometer times, we loop through the vector of palindromes, subtract the first value of the pair from the second
	value of the pair to get the miles that must be driven to get to the next palindrome value on the odometer
	*/

	vector<pair<string,string>> originalAndPalindromes;

	int miles; 

	string milesCopy;

	string reversedMiles;
	
	string milesAsString;

	string reversedMilesAsString;

	int x;
	for(x=0;x<OdometerReadings.size();++x)
	{
		cout << "LOOKING AT: " << OdometerReadings.at(x) << "\n";

		milesAsString=OdometerReadings.at(x);

		//convert reverse of original odometer value to string
		reversedMilesAsString=string{ milesAsString.rbegin(), milesAsString.rend() };

		//comapre the strings to see if we have a palindrome
		if(reversedMilesAsString==milesAsString)
		{
			cout << "Neartest palindrome: " << reversedMilesAsString  << "\n";

			cout << "\n";

			//add palindromes to vector
			originalAndPalindromes.emplace_back(make_pair(milesAsString, reversedMilesAsString));
		}
		else
		{
			int length;

			int length2;

			int leadingZerosToAdd=0;

			//get size of string before we conver to int so we know how many leading zeros to add
			length=OdometerReadings.at(x).length();

			//convert string representation of miles to int
			miles=stoi(OdometerReadings.at(x));

			do
			{
				miles++;

				//convert miles back to string since we have lost the leading zeros in the string to int conversion
				milesCopy=to_string(miles);

				length2=milesCopy.length();

				leadingZerosToAdd=length-length2;

				int counter=0;

				//addin the leading zeros back onto string 
				while(counter<leadingZerosToAdd)
				{
					milesCopy='0'+milesCopy;

					counter++;
				}

				reversedMiles=string {milesCopy.rbegin(), milesCopy.rend() };

				//check for palindrome
				if(reversedMiles==milesCopy)
				{
					cout << "Neartest palindrome: "  << reversedMiles << "\n";

					cout << "\n";

					originalAndPalindromes.emplace_back(make_pair(OdometerReadings.at(x), reversedMiles));					

					break;
				}
			}
			while(true);
		}
	}

	for(const auto pair : originalAndPalindromes)
	{
		cout << "\n";

		cout << "The nearest palindrome of " << pair.first << " is " << pair.second << "\n";

		cout << "The mileage difference between " << pair.second << " and " << pair.first << " is: "  << stoi(pair.second)-stoi(pair.first) << "\n";
	}	
}

int main()
{
	vector<string> odometerReadings;

	odometerReadings=readInFile("./data.txt");

	cout << "odometer readings:" << "\n";

	copy(odometerReadings.cbegin(), odometerReadings.cend(), ostream_iterator<string>(cout, " "));

	cout << "\n";

	cout << "\n";

	doPalindromeMeter(odometerReadings);	
}	