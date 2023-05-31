#include "FileController.h"



bool FileController::openFile(string fileToOpen)
{
	_fileName = fileToOpen;
	ifstream in(_fileName, std::ios::out | std::ios::binary);
	if (!in) {
		std::cout << fileToOpen << " not found. Creating file..." << std::endl;
		ofstream out(_fileName, std::ios::out | std::ios::trunc);
		out.close();;
		return false; //returns false as file is not open yet.
	}

	size_t fileSize = getFileSize(in);	

	
	while (in.tellg() < fileSize)
	{
		Serializable* temp = Serializable::readSerializable(in);
		_fileItemList.push_back(temp);
	}
	in.close();
	_isFileOpen = in.good();
	return in.good();
}

bool FileController::save() const
{
	return saveAs(_fileName);
}

bool FileController::saveAs(string targetFileName) const
{
	ofstream out(targetFileName, std::ios::binary | std::ios::trunc);
	if (!out) {
		throw "Failed to load file!";
		return false;
	}
	for (Serializable* serializable : _fileItemList) {
		serializable->serialize(out);
	}
	out.close();
	return out.good();
}

bool FileController::close()
{
	if (!_isFileOpen) {
		std::cout << "No file open!";
		return false;
	}
	_isFileOpen = false;
	freeItemList();
	std::cout << "Closed " << _fileName << std::endl;
	return true;
}

bool FileController::isOpen() const
{
	return _isFileOpen;
}

void FileController::freeItemList()
{
	_fileItemList.clear();
}

void FileController::showAllBooks() const
{
	for (Serializable* book : _fileItemList) {
		book->printForAll();
		printNewline();
	}
}

bool FileController::showBookDetails(const unsigned id)
{
	for (size_t i = 0; i < _fileItemList.size(); i++)
	{
		if (_fileItemList[i]->checkForDetails(id))
			return true;
	}
	return false;
	

}

size_t FileController::getFileSize(ifstream& in)
{
	in.seekg(0, SEEK_END);
	size_t fileSize = in.tellg();
	in.seekg(0, SEEK_SET);
	return fileSize;
}

