#include "Book.h"

void Book::copy(const Book& other)
{
	_author = other._author;
	_title = other._title;
	_genre = other._genre;
	_description = other._description;
	_year = other._year;
	_tags = other._tags;
	_rating = other._rating;
	_id = other._id;
}

Book::Book()
{
	_author.reserve(16);
	_title.reserve(16);
	_genre.reserve(16);
	_description.reserve(16);
	_year = 2023;
	_tags.reserve(4);
	_rating = 0;
	_id = 0;
}
//
Book::Book(const string& author, const string& title, const string& genre, const string& desc, const unsigned year, const vector<string>& tags, const double rating, unsigned id)
{
	_author = author;
	_title = title;
	_genre = genre;
	_description = desc;
	_year = year;
	_tags = tags;
	_rating = rating;
	_id = id;
}

//Book& Book::operator=(const Book& other)
//{
//	copy(other);
//	return *this;
//}

bool Book::generateBooksFile(string fileName)
{
	Book b1("John Michaels", "COOL BOOK", "COMEDY", "The greatest book ever", 2010, { "super", "cool reading", "book" }, 4.5, 27);
	Book b2("Andy Rillins", "Book about Magic", "Adventure", "Magic", 2002, { "magic", "friendship" }, 9.5, 24);
	Book b3("Oliver Dann", "The Depth", "Action", "Action", 2017, { "action" }, 1.7, 23);
	Book b4("Mark Irivine", "Hell and Heaven", "Drama", "Book about the lifecycle", 2007, { "drama", "hell", "heaven" }, 2.7, 13);
	Book b5("Tamara Neil", "Fancy book", "Comedy", "Comedy books", 2011, { "fancy tag" }, 5.6, 14);

	ofstream out(fileName, std::ios::out | std::ios::binary);
	b1.serialize(out);
	b2.serialize(out);
	b3.serialize(out);
	b4.serialize(out);
	b5.serialize(out);
	out.close();
	return out.good();
}

bool Book::readBook(ifstream& in, Book& book) {
	string serializable;
	Serializable::readStringFromBinary(serializable, in);
	if (serializable != BOOK_OBJECT_SIGNATURE) {
		throw "Invalid file contents";
		return false;
	}
	book.deserialize(in);
	return in.good();
}

bool Book::serialize(ofstream& out)
{
	if (!(writeStringToBinary(BOOK_OBJECT_SIGNATURE, out)
		&& writeStringToBinary(_author, out)
		&& writeStringToBinary(_title, out)
		&& writeStringToBinary(_genre, out)
		&& writeStringToBinary(_description, out))) {
			throw "Failed to write to file!";
			return false;
		}
	
	out.write((char*)&_year, sizeof(_year));

	size_t size = _tags.size();
	out.write((char*)&size, sizeof(size_t));
	for (string tag : _tags) {
		if (!writeStringToBinary(tag, out)) {
			throw "Failed to write to file!";
		}
	}

	out.write((char*)&_rating, sizeof(_rating));
	out.write((char*)&_id, sizeof(_id));
	return out.good();
}

bool Book::deserialize(ifstream& in)
{
	if (!(readStringFromBinary(_author, in)
		&& readStringFromBinary(_title, in)
		&& readStringFromBinary(_genre, in)
		&& readStringFromBinary(_description, in))) {
			throw "Failed to read from file!";
			return false;
	}

	in.read((char*)&_year, sizeof(_year));
	
	size_t size;
	in.read((char*)&size, sizeof(size));
	_tags.resize(size);
	for (size_t i = 0; i < size; ++i)
	{
		if (!readStringFromBinary(_tags[i], in)) {
			throw "Failed to read from file!";
			return false;
		}
	}

	in.read((char*)&_rating, sizeof(_rating));
	in.read((char*)&_id, sizeof(_id));
	return in.good();
}

void Book::printDetails() const
{
		this->printForAll();
		std::cout 
			<< "Year: " << _year << '\n' 
			<< "Tags: ";
		for (string tag : _tags)
		{
			std::cout << tag << ' ';
		}

		std::cout << '\n' 
				  << "Rating: " << _rating << '\n' 
				  << "Id: " << _id << '\n';
}

void Book::printForAll() const
{
		std::cout 
			<< "Author: " << _author << '\n' 
			<< "Title: " << _title << '\n' 
			<< "Genre: " << _genre << '\n' 
			<< "Description: " << _description << '\n';
}

bool Book::checkForDetails(const unsigned id) const
{
	if (id == _id) {
		printDetails();
		return true;
	}
	return false;
}

void Book::setAll()
{
	//TODO: some extra validation for numbers
	string tempStr;
	long tempNum;

	std::cout << "Author: ";
	getline(std::cin, _author);

	std::cout << "Title: ";
	getline(std::cin, _title);

	std::cout << "Genre: ";
	getline(std::cin, _genre);

	std::cout << "Description: ";
	getline(std::cin, _description);

	std::cout << "Year: ";
	while (true) {
		if (std::cin >> tempNum) {
			//valid number
			if (tempNum < 0) {
				std::cout << "Please enter a valid year.";
				continue;
			}
			_year = tempNum;
			break;
		}
		else {
			//invalid number
			std::cout << "Invalid input! Please try again: ";
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
	}

	std::cout << "Number of tags: ";
	while (true) {
		if (std::cin >> tempNum) {
			//valid number
			break;
		}
		else {
			//invalid number
			std::cout << "Invalid input! Please try again: ";
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
	}

	for (size_t i = 0; i < tempNum; ++i)
	{
		std::cout << "Tag #" << i << ": ";
		getline(std::cin, tempStr);
		_tags.push_back(tempStr);
	}

	std::cout << "Rating: ";
	while (true) {
		if (std::cin >> _rating) {
			//valid number
			break;
		}
		else {
			//invalid number
			std::cout << "Invalid input! Please try again: ";
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
	}

	//TODO: Extra validation to check if a book with corresponding ID already exists.
	std::cout << "Id: ";
	while (true) {
		if (std::cin >> tempNum) {
			//valid number
			if (tempNum < 0) {
				std::cout << "Please enter a valid id.";
				continue;
			}
			_id = tempNum;
			break;
		}
		else {
			//invalid number
			std::cout << "Invalid input! Please try again: ";
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
	}
}
