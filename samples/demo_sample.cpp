#include <stdio.h>
#include <string>
#include "file_html5skeleton.h" //a single include file is all you need

int main(int argc, char* argv[])
{
  //get a reference to the embedded file
  const bin2cpp::File & resource = bin2cpp::getHtmlSampleFile();

  //print information about the file.
  printf("Embedded file '%s' is %lu bytes long.\n", resource.getFilename(), resource.getSize());

  //Saving content back to a file.
  printf("Saving embedded file to 'html5skeleton_copy.html'...\n");
  bool saved = resource.save("html5skeleton_copy.html");
  if (saved)
    printf("saved\n");
  else
    printf("failed\n");

  //Get the internal buffer and do something with the binary data
  const char * buffer = resource.getBuffer();
  size_t bufferSize = resource.getSize();
  //...
  
  return 0;
}
