#include <globals.h>

void test_int(object me, mixed iValue, mixed strValue)
{
    int iTemp;

    write("**************************************\n");

    sscanf(strValue, "%d", iTemp);
    write(strValue + "=");
    write("" + iTemp);
    write("\n");

    write("iValue=");
    write("" + iValue);
    write("\n");
    printf("printf %%d=%d", iValue);
    write("\n");
    write(sprintf("sprintf %%d=%d", iValue));
    write("\n");

    write("-iValue=");
    write("" + (-iValue));
    write("\n");
    printf("printf %%d=%d", -iValue);
    write("\n");
    write(sprintf("sprintf %%d=%d", -iValue));
    write("\n");

    write("iValue-1=");
    write("" + (iValue-1));
    write("\n");
    printf("printf %%d=%d", iValue-1);
    write("\n");
    write(sprintf("sprintf %%d=%d", iValue-1));
    write("\n");

    iTemp = iValue;
    iTemp--;
    write("iValue--=");
    write("" + iTemp);
    write("\n");
    printf("printf %%d=%d", iTemp);
    write("\n");
    write(sprintf("sprintf %%d=%d", iTemp));
    write("\n");

    write("iValue+1=");
    write("" + (iValue+1));
    write("\n");
    printf("printf %%d=%d", iValue+1);
    write("\n");
    write(sprintf("sprintf %%d=%d", iValue+1));
    write("\n");

    iTemp = iValue;
    iTemp++;
    write("iValue++=");
    write("" + iTemp);
    write("\n");
    printf("printf %%d=%d", iTemp);
    write("\n");
    write(sprintf("sprintf %%d=%d", iTemp));
    write("\n");

    write("**************************************\n");
}

void test_float(object me, mixed iValue, mixed strValue)
{
    mixed iTemp;

    write("**************************************\n");

    sscanf(strValue, "%f", iTemp);
    write(strValue + "=");
    write("" + iTemp);
    write("\n");

    write("iValue=");
    write("" + iValue);
    write("\n");
    printf("printf %%f=%f", iValue);
    write("\n");
    write(sprintf("sprintf %%f=%f", iValue));
    write("\n");

    write("-iValue=");
    write("" + (-iValue));
    write("\n");
    printf("printf %%f=%f", -iValue);
    write("\n");
    write(sprintf("sprintf %%f=%f", -iValue));
    write("\n");

    write("iValue+1=");
    write("" + (iValue+1));
    write("\n");
    printf("printf %%f=%f", iValue+1);
    write("\n");
    write(sprintf("sprintf %%f=%f", iValue+1));
    write("\n");

    write("**************************************\n");
}

int main(object me, string args)
{
/*
#define INT8_MIN         (-127 - 1)
#define INT16_MIN        (-32767 - 1)
#define INT32_MIN        (-2147483647 - 1)
#define INT64_MIN        (-9223372036854775807 - 1)
#define INT8_MAX         1
#define INT16_MAX        32767
#define INT32_MAX        2147483647
#define INT64_MAX        9223372036854775807
#define UINT8_MAX        0xff
#define UINT16_MAX       0xffff
#define UINT32_MAX       0xffffffff
#define UINT64_MAX       0xffffffffffffffff

#define FLT_MAX          3.402823466e+38        // max value
#define FLT_MIN          1.175494351e-38        // min normalized positive value
#define FLT_TRUE_MIN     1.401298464e-45        // min positive value
#define DBL_MAX          1.7976931348623158e+308 // max value
#define DBL_MIN          2.2250738585072014e-308 // min positive value
#define DBL_TRUE_MIN     4.9406564584124654e-324 // min positive value
*/

    write("test int\n");

    test_int(me, -128, "-128");
    test_int(me, -129, "-129");
    test_int(me, -32768, "-32768");
    test_int(me, -32769, "-32769");
    test_int(me, -2147483648, "-2147483648");
    test_int(me, -2147483649, "-2147483649");
    test_int(me, -9223372036854775806, "-9223372036854775806");
    test_int(me, -9223372036854775807, "-9223372036854775807");
    test_int(me, 127, "127");
    test_int(me, 128, "128");
    test_int(me, 32767, "32767");
    test_int(me, 32768, "32768");
    test_int(me, 2147483647, "2147483647");
    test_int(me, 2147483648, "2147483648");
    test_int(me, 9223372036854775806, "9223372036854775806");
    test_int(me, 9223372036854775807, "9223372036854775807");
    test_int(me, 255, "255");
    test_int(me, 256, "256");
    test_int(me, 65535, "65535");
    test_int(me, 65536, "65536");
    test_int(me, 4294967295, "4294967295");
    test_int(me, 4294967296, "4294967296");

    write("test float\n");

    test_float(me, -2147483648.000000 , "-2147483648.000000");
    test_float(me, 2147483647.000000 , "2147483647.000000");
    test_float(me, -4294967296.000000 , "-4294967296.000000");
    test_float(me, 4294967295.000000 , "4294967295.000000");
    test_float(me, -340282346638528859811704183484516925440.000000 , "-340282346638528859811704183484516925440.000000");
    test_float(me, 340282346638528859811704183484516925440.000000 , "340282346638528859811704183484516925440.000000");

    return 1;
}

