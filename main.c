#include <stdio.h>
#include <string.h>
#include "crypto/mbedtls/sha256.h"

#define BUFFER_SIZE 1024 // 定义缓冲区大小

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb"); // 以二进制模式打开文件
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    unsigned char buffer[BUFFER_SIZE];
    unsigned char output[32];
    int ret;
    size_t bytes_read;

    mbedtls_sha256_context ctx;
    mbedtls_sha256_init(&ctx);

    ret = mbedtls_sha256_starts_ret(&ctx, 0); // 初始化 SHA256 上下文
    if (ret != 0) {
        printf("SHA256 starts failed: %d\n", ret);
        goto cleanup;
    }

    // 分块读取文件并更新哈希
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        ret = mbedtls_sha256_update_ret(&ctx, buffer, bytes_read);
        if (ret != 0) {
            printf("SHA256 update failed: %d\n", ret);
            goto cleanup;
        }
    }

    // 检查文件读取是否出错
    if (ferror(file)) {
        perror("Error reading file");
        ret = -1;
        goto cleanup;
    }

    ret = mbedtls_sha256_finish_ret(&ctx, output); // 完成哈希计算
    if (ret != 0) {
        printf("SHA256 finish failed: %d\n", ret);
        goto cleanup;
    }

    // 打印哈希值
    for (int i = 0; i < 32; i++) {
        printf("%02x", output[i]);
    }
    printf("\n");

    cleanup:
    mbedtls_sha256_free(&ctx);
    fclose(file); // 关闭文件
    return ret;
}
