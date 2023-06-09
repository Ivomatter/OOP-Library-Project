#pragma once


//Base class to be inherited by all classes which have to support serialization

#include <fstream>
#include <string>

using std::string;
using std::ofstream;
using std::ifstream;

class Serializable
{
public:
	static bool writeStringToBinary(const string& str, ofstream& out);
	static bool readStringFromBinary(string& str, ifstream& in);

	static Serializable* readSerializable(ifstream& in);

	virtual bool serialize(ofstream& out) = 0;
	virtual bool deserialize(ifstream& out) = 0;

	virtual void printDetails() const = 0;
	virtual void printForAll() const = 0;

	virtual bool checkForDetails(const unsigned id) const = 0;

	virtual string getName() = 0;

	virtual void setAll() = 0;
};

