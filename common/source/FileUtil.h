#ifndef COMMON_FILEUTIL_H
#define COMMON_FILEUTIL_H

#include <io/InputStream.h>

class FileUtil
{
public:
	std::vector<unsigned char> loadFile(const std::string& filePath);
	
	void decrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out);
	
	void decompress(InputStream& input, std::vector<unsigned char>& output);
	
	//These might only be in ABClassic.
	/*void loadFile(io::InputStream&);
	void getEncryptionKey();
	bool areLuaFilesZipped();
	void loadAssetFile();*/
};

#endif