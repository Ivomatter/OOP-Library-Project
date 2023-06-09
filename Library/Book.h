#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Serializable.h"
#include "Constants.h"


using std::string;
using std::vector;


class Book : public Serializable
{
private:
	string _author;
	string _title;
	string _genre;
	string _description;
	unsigned _year;
	vector<string> _tags;
	double _rating;
	unsigned _id;

	void copy(const Book& other);
public:
	Book();
	Book(const string& author, const string& title, const string& genre, const string& desc) : _author(author), _title(title), _genre(genre), _description(desc) { _year = 2023; _rating = 0; _id = -1; };
	Book(const string& author,const string& title, const string& genre, const string& desc, const unsigned year,const vector<string>& tags, const double rating, unsigned id);

	//Book& operator=(const Book& other);
	
	static bool generateBooksFile(string fileName);
	static bool readBook(ifstream& in, Book& temp);

	bool serialize(ofstream& out) override final;
	bool deserialize(ifstream& in) override final;

	void printDetails() const override final;
	void printForAll() const override final;

	bool checkForDetails(const unsigned id) const override final;
	
	string getName() override final { return _author; }
	string getAuthor() const { return _author; }
	string getTitle() const { return _title; }
	vector<string> getTags() const { return _tags; }

	void setAll() override final;
};


