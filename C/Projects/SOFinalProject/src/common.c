#include "../include/common.h"

void Write(int fd, const void* buff, size_t len, processType pType){
     snprintf(writeBuffer,WRITE_BUFFER_LEN,"%s%s%s%s",precolor,colors[pType],(char*)buff,blank);
     write(fd,writeBuffer,WRITE_BUFFER_LEN);
     bzero(&writeBuffer, WRITE_BUFFER_LEN);
}
