#include "BaseGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdlib.h>

#include "common.h"

namespace bin2cpp
{
  BaseGenerator::BaseGenerator()
  {
  }

  BaseGenerator::~BaseGenerator()
  {
  }

  std::string BaseGenerator::getGetterFunctionName(const char * iFunctionIdentifier)
  {
    //Uppercase function identifier
    std::string functionIdentifier = iFunctionIdentifier;
    functionIdentifier[0] = (char)toupper(functionIdentifier[0]);

    std::string getter;
    getter.append("get");
    getter.append(functionIdentifier);
    getter.append("File");
    return getter;
  }

  std::string BaseGenerator::getHeaderFilePath(const char * iCppFilePath)
  {
    //Build header file path
    std::string headerPath = iCppFilePath;
    strReplace(headerPath, ".cpp", ".h");
    return headerPath;
  }

  std::string BaseGenerator::getCppFilePath(const char * iHeaderFilePath)
  {
    //Build header file path
    std::string cppPath = iHeaderFilePath;
    strReplace(cppPath, ".cpp", ".h");
    return cppPath;
  }

  std::string BaseGenerator::getFileHeading(const char * iInputFilename)
  {
    std::string filename = getFilename(iInputFilename);
    uint64_t lastModifiedDate = getFileModifiedDate(iInputFilename);

    std::string header;
    header << 
    header << "/**\n";
    header << " * This file was generated by bin2cpp v" << getVersionString() << "\n";
    header << " * Copyright (C) 2013-" << bin2cpp::getCopyrightYear() << " end2endzone.com. All rights reserved.\n";
    header << " * bin2cpp is open source software, see http://github.com/end2endzone/bin2cpp\n";
    header << " * Source code for file '" << filename << "', last modified " << lastModifiedDate << ".\n";
    header << " * Do not modify this file.\n";
    header << " */\n";
    return header;
  }

  std::string BaseGenerator::getSaveMethodImplementation()
  {
    std::string output;
    output << "    virtual bool save(const char * iFilename) const\n";
    output << "    {\n";
    output << "      FILE * f = fopen(iFilename, \"wb\");\n";
    output << "      if (!f) return false;\n";
    output << "      size_t fileSize = getSize();\n";
    output << "      const char * buffer = getBuffer();\n";
    output << "      fwrite(buffer, 1, fileSize, f);\n";
    output << "      fclose(f);\n";
    output << "      return true;\n";
    output << "    }\n";
    return output;
  }

  bool BaseGenerator::createCppHeaderFile(const char * iInputFilename, const char * iHeaderFilePath, const char * iFunctionIdentifier)
  {
    FILE * header = fopen(iHeaderFilePath, "w");
    if (!header)
      return false;

    std::string headercomments = getFileHeading(iInputFilename);
    fprintf(header, "%s", headercomments.c_str());
    fprintf(header, "#pragma once\n");
    fprintf(header, "#include <stddef.h>\n");
    fprintf(header, "namespace bin2cpp\n");
    fprintf(header, "{\n");
    fprintf(header, "  #ifndef BIN2CPP_EMBEDDEDFILE_CLASS\n");
    fprintf(header, "  #define BIN2CPP_EMBEDDEDFILE_CLASS\n");
    fprintf(header, "  class File\n");
    fprintf(header, "  {\n");
    fprintf(header, "  public:\n");
    fprintf(header, "    virtual size_t getSize() const = 0;\n");
    fprintf(header, "    virtual const char * getFilename() const = 0;\n");
    fprintf(header, "    virtual const char * getBuffer() const = 0;\n");
    fprintf(header, "    virtual bool save(const char * iFilename) const = 0;\n");
    fprintf(header, "  };\n");
    fprintf(header, "  #endif\n");
    fprintf(header, "  const File & %s();\n", getGetterFunctionName(iFunctionIdentifier).c_str());
    fprintf(header, "}; //bin2cpp\n");

    fclose(header);

    return true;
  }

}; //bin2cpp