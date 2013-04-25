#include <QtGui/QApplication>
#include "reportermv.h"
#include <windows.h>
#include <iostream>
#include <QDebug>

using namespace std;

UINT64 get_cpuid(void)
{
   DWORD dS = 0;
   DWORD dF = 0;

   asm( "mov $1,%eax");
   asm( "cpuid\n\t");
   asm( "mov %%eax ,%0" : "=r" (dS) );
   asm( "mov %%edx ,%0" : "=r" (dF) );
    return( ((UINT64)(dF) << 32) | ((UINT64)(dS)));
}

int main(int argc, char *argv[])
{

    UINT64 name = get_cpuid();
    QApplication a(argc, argv);
    ReporterMV w(name);
    if(w.showed)
        w.show();
    else
        return 0;
    return a.exec();
}
