#include "stdio.h"
#include "String.h"
#include "new.h"

/*
output:
sizeOf(a) == 8
ok
*/
int     main()
{
    void    *a = new(String, "a");
    void    *aa = clone(a);
    void    *b = new(String, "b");

    printf("sizeOf(a) ==  %zu\n", sizeOf(a));

    if (differ(a, b))
        puts("ok");

    if (differ (a, aa))
        puts("differ?");

    if (a == aa)
        puts("clone?");

    delete(a), delete(aa), delete(b);
    return 0;
}
