#ifndef _COMMON_FILEUTIL_H
#define _COMMON_FILEUTIL_H

#include <io/InputStream.h>

namespace io { //6
	class BundleInputStream;
	class ByteArrayInputStream;
	class InputStream;
	class MemoryAliasInputStream;
	class ZipEntryInputStream; class ZipFile; class ZipFileInputStream;
}

namespace FileUtil
{
public:
	std::vector<std::string> loadFile(const std::string& filePath); //17
	
	void decrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out); //37
	
	void decompress(io::InputStream& input, std::vector<unsigned char>& output); //45
	
	//These might only be in ABClassic.
	/*void loadFile(io::InputStream&);
	void getEncryptionKey();
	bool areLuaFilesZipped();
	void loadAssetFile();*/
};

#endif