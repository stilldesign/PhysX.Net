#ifndef NXU_FILE_H

#define NXU_FILE_H

namespace NXU
{

class NXU_FILE;

NXU_FILE * nxu_fopen(const char *fname,const char *spec,void *mem=0,int len=0);
void       nxu_fclose(NXU_FILE *file);
int        nxu_fread(void *buffer,int size,int count,NXU_FILE *fph);
int        nxu_fwrite(const void *buffer,int size,int count,NXU_FILE *fph);
int        nxu_fprintf(NXU_FILE *fph,const char *fmt,...);
int        nxu_fflush(NXU_FILE *fph);
int        nxu_fseek(NXU_FILE *fph,int loc,int mode);
int        nxu_ftell(NXU_FILE *fph);
int        nxu_fputc(char c,NXU_FILE *fph);
int        nxu_fputs(const char *str,NXU_FILE *fph);
int        nxu_feof(NXU_FILE *fph);
int        nxu_ferror(NXU_FILE *fph);
void *     nxu_getMemBuffer(NXU_FILE *fph,int &outputLength);

}; // end of NXU namespace

#endif
