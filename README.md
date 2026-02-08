# 02_mebedtls_hashtest
sha256
1.实现文件计算sha256

2.注意：修改 mbedtls/config.h，
#define MBEDTLS_NET_C 更改为 #undef MBEDTLS_NET_C
3. .\hashtest_file.exe filename
