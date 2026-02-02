#include <stdio.h>
#include <string.h>
#include <crypto/mbedtls/sha256.h>

int main(void)
{
    const unsigned char input[] = "hello mbedtls";
    unsigned char output[32];
    int ret;

    mbedtls_sha256_context ctx;
    mbedtls_sha256_init(&ctx);

    ret = mbedtls_sha256_starts_ret(&ctx, 0); // SHA256
    if (ret != 0) {
        printf("SHA256 starts failed: %d\n", ret);
        goto exit;
    }

    ret = mbedtls_sha256_update_ret(&ctx, input, strlen((const char *)input));
    if (ret != 0) {
        printf("SHA256 update failed: %d\n", ret);
        goto exit;
    }

    ret = mbedtls_sha256_finish_ret(&ctx, output);
    if (ret != 0) {
        printf("SHA256 finish failed: %d\n", ret);
        goto exit;
    }

    // 打印 hash
    for (int i = 0; i < 32; i++) {
        printf("%02x", output[i]);
    }
    printf("\n");

    exit:
    mbedtls_sha256_free(&ctx);
    return ret;
}
