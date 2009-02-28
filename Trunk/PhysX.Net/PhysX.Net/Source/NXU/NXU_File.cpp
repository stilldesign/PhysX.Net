#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "NXU_File.h"
#include "NXU_string.h"

#ifdef _MSC_VER
#pragma warning(disable:4996) // Disabling stupid .NET deprecated warning.
#endif

namespace NXU
{

#define DEFAULT_BUFFER_SIZE 1000000
#define DEFAULT_GROW_SIZE   2000000

#if defined(LINUX)
#   define _stricmp(a,b) strcasecmp((a),(b))
#endif

class NXU_FILE
{
public:
	NXU_FILE(const char *fname,const char *spec,void *mem,int len)
	{
		mMyAlloc = false;
		mRead = true; // default is read access.
		mFph = 0;
		mData = (char *) mem;
		mLen  = len;
		mLoc  = 0;

		if ( spec && _stricmp(spec,"wmem") == 0 )
		{
			mRead = false;
			if ( mem == 0 || len == 0 )
			{
				mData = new char[DEFAULT_BUFFER_SIZE];
				mLen  = DEFAULT_BUFFER_SIZE;
				mMyAlloc = true;
			}
		}

		if ( mData == 0 )
		{
			mFph = fopen(fname,spec);
		}

  	strncpy(mName,fname,512);
	}

  ~NXU_FILE(void)
  {
  	if ( mMyAlloc )
  	{
  		delete mData;
  	}
  	if ( mFph )
  	{
  		fclose(mFph);
  	}
  }

  int read(char *data,int size)
  {
  	int ret = 0;
  	if ( (mLoc+size) <= mLen )
  	{
  		memcpy(data, &mData[mLoc], size );
  		mLoc+=size;
  		ret = 1;
  	}
    return ret;
  }

  int write(const char *data,int size)
  {
  	int ret = 0;

		if ( (mLoc+size) >= mLen && mMyAlloc ) // grow it
		{
			int newLen = mLen+DEFAULT_GROW_SIZE;
			if ( size > newLen ) newLen = size+DEFAULT_GROW_SIZE;

			char *data = new char[newLen];
			memcpy(data,mData,mLoc);
			delete mData;
			mData = data;
			mLen  = newLen;
		}

  	if ( (mLoc+size) <= mLen )
  	{
  		memcpy(&mData[mLoc],data,size);
  		mLoc+=size;
  		ret = 1;
  	}
  	return ret;
  }

	int read(void *buffer,int size,int count)
	{
		int ret = 0;
		if ( mFph )
		{
			ret = (int) fread(buffer,size,count,mFph);
		}
		else
		{
			char *data = (char *)buffer;
			for (int i=0; i<count; i++)
			{
				if ( (mLoc+size) <= mLen )
				{
					read(data,size);
					data+=size;
					ret++;
				}
				else
				{
					break;
				}
			}
		}
		return ret;
	}

  int write(const void *buffer,int size,int count)
  {
  	int ret = 0;

  	if ( mFph )
  	{
  		ret = (int)fwrite(buffer,size,count,mFph);
  	}
  	else
  	{
  		const char *data = (const char *)buffer;

  		for (int i=0; i<count; i++)
  		{
    		if ( write(data,size) )
				{
    			data+=size;
    			ret++;
    		}
    		else
    		{
    			break;
    		}
  		}
  	}
  	return ret;
  }

  int writeString(const char *str)
  {
  	int ret = 0;
  	if ( str )
  	{
  		int len = (int)strlen(str);
  		ret = write(str,len, 1 );
  	}
  	return ret;
  }


  int  flush(void)
  {
  	int ret = 0;
  	if ( mFph )
  	{
  		ret = fflush(mFph);
  	}
  	return ret;
  }


  int seek(int loc,int mode)
  {
  	int ret = 0;
  	if ( mFph )
  	{
  		ret = fseek(mFph,loc,mode);
  	}
  	else
  	{
  		if ( mode == SEEK_SET )
  		{
  			if ( loc <= mLen )
  			{
  				mLoc = loc;
  				ret = 1;
  			}
  		}
  		else if ( mode == SEEK_END )
  		{
  			mLoc = mLen;
  		}
  		else
  		{
  			assert(0);
  		}
  	}
  	return ret;
  }

  int tell(void)
  {
  	int ret = 0;
  	if ( mFph )
  	{
  		ret = ftell(mFph);
  	}
  	else
  	{
  		ret = mLoc;
  	}
  	return ret;
  }

  int myputc(char c)
  {
  	int ret = 0;
  	if ( mFph )
  	{
  		ret = fputc(c,mFph);
  	}
  	else
  	{
  		ret = write(&c,1);
  	}
  	return ret;
  }

  int eof(void)
  {
  	int ret = 0;
  	if ( mFph )
  	{
  		ret = feof(mFph);
  	}
  	else
  	{
  		if ( mLoc >= mLen )
  			ret = 1;
  	}
  	return ret;
  }

  int  error(void)
  {
  	int ret = 0;
  	if ( mFph )
  	{
  		ret = ferror(mFph);
  	}
  	return ret;
  }


  FILE 	*mFph;
  char  *mData;
  int    mLen;
  int    mLoc;
  bool   mRead;
	char   mName[512];
	bool   mMyAlloc;

};

NXU_FILE * nxu_fopen(const char *fname,const char *spec,void *mem,int len)
{
	NXU_FILE *ret = 0;

	ret = new NXU_FILE(fname,spec,mem,len);

	if ( mem == 0 && ret->mData == 0)
  {
  	if ( ret->mFph == 0 )
  	{
  		delete ret;
  		ret = 0;
  	}
  }

	return ret;
}

void       nxu_fclose(NXU_FILE *file)
{
	delete file;
}

int        nxu_fread(void *buffer,int size,int count,NXU_FILE *fph)
{
	int ret = 0;
	if ( fph )
	{
		ret = fph->read(buffer,size,count);
	}
	return ret;
}

int        nxu_fwrite(const void *buffer,int size,int count,NXU_FILE *fph)
{
	int ret = 0;
	if ( fph )
	{
		ret = fph->write(buffer,size,count);
	}
	return ret;
}

int        nxu_fprintf(NXU_FILE *fph,const char *fmt,...)
{
	int ret = 0;

	char buffer[2048];

    va_list ap;
	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);

	if ( fph )
	{
		ret = fph->writeString(buffer);
	}

	return ret;
}


int        nxu_fflush(NXU_FILE *fph)
{
	int ret = 0;
	if ( fph )
	{
		ret = fph->flush();
	}
	return ret;
}


int        nxu_fseek(NXU_FILE *fph,int loc,int mode)
{
	int ret = 0;
	if ( fph )
	{
		ret = fph->seek(loc,mode);
	}
	return ret;
}

int        nxu_ftell(NXU_FILE *fph)
{
	int ret = 0;
	if ( fph )
	{
		ret = fph->tell();
	}
	return ret;
}

int        nxu_fputc(char c,NXU_FILE *fph)
{
	int ret = 0;
	if ( fph )
	{
		ret = fph->myputc(c);
	}
	return ret;
}

int        nxu_fputs(const char *str,NXU_FILE *fph)
{
	int ret = 0;
	if ( fph )
	{
		ret = fph->writeString(str);
	}
	return ret;
}

int        nxu_feof(NXU_FILE *fph)
{
	int ret = 0;
	if ( fph )
	{
		ret = fph->eof();
	}
	return ret;
}

int        nxu_ferror(NXU_FILE *fph)
{
	int ret = 0;
	if ( fph )
	{
		ret = fph->error();
	}
	return ret;
}

void *     nxu_getMemBuffer(NXU_FILE *fph,int &outputLength)
{
	outputLength = 0;
	void * ret = 0;
	if ( fph )
	{
		ret = fph->mData;
		outputLength = fph->mLoc;
		fph->mMyAlloc = false;
	}
	return ret;
}

}; // end of NXU namespace
