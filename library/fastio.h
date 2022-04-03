/*
MIT license

Copyright 2022 harurun

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#define read_size 1000000
#define write_size 1000000

struct fastio{
  private:
    char read_data[read_size];
    char *read_buffer=read_data;
    char write_data[write_size];
    char *write_buffer=write_data;
    void readspeoln(){
      while(*read_buffer==' '||*read_buffer=='\n'||*read_buffer=='\r')*read_buffer++;
    }
  public:
    fastio(){
      fread(read_data,1,read_size,stdin);
    }
    // plus only
    void readint(int &x){
      readspeoln();
      for(x=*read_buffer++&15;*read_buffer>='0' && *read_buffer<='9';){
        x=x*10+(*read_buffer++&15);
      }
    }
    void readll(long long &x){
      readspeoln();
      for(x=*read_buffer++&15;*read_buffer>='0' && *read_buffer<='9';){
        x=x*10+(*read_buffer++&15);
      }
    }
    // [a,z]
    void readstr(char *s){
      readspeoln();
      for(;*read_buffer>='a'&&*read_buffer<='z';*s++){
        *s=*read_buffer++;
      }
    }
    void write(char s){
      *write_buffer++=s;
    }
    ~fastio(){
      if(write_buffer-write_data!=0)fwrite(write_data,1,write_buffer-write_data,stdout);
    }
};

