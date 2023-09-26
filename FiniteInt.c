#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    
    printf("Size of int8_t: %zu bits\n", 8 * sizeof(int8_t));
    printf("Signed int8_t range: %" PRId8 " to %" PRId8 "\n", INT8_MIN, INT8_MAX);
    printf("\n");
    
    printf("Size of uint8_t: %zu bits\n", 8 * sizeof(uint8_t));
    printf("uint8_t range: %d to %" PRIu8 "\n", 0, UINT8_MAX);
    printf("\n");
    
    printf("Size of int16_t: %zu bits\n", 8 * sizeof(int16_t));
    printf("Signed int16_t range: %" PRId16 " to %" PRId16 "\n", INT16_MIN, INT16_MAX);
    printf("\n");
    
    printf("Size of uint16_t: %zu bits\n", 8 * sizeof(uint16_t));
    printf("uint16_t range: %d to %" PRIu16 "\n", 0, UINT16_MAX);
    printf("\n");
    
    printf("Size of int32_t: %zu bits\n", 8 * sizeof(int32_t));
    printf("Signed int32_t range: %" PRId32 " to %" PRId32 "\n", INT32_MIN, INT32_MAX);
    printf("\n");
    
    printf("Size of uint32_t: %zu bits\n", 8 * sizeof(uint32_t));
    printf("uint32_t range: %d to %" PRIu32 "\n", 0, UINT32_MAX);
    printf("\n");
    
    printf("Size of int64_t: %zu bits\n", 8 * sizeof(int64_t));
    printf("Signed int64_t range: %" PRId64 " to %" PRId64 "\n", INT64_MIN, INT64_MAX);
    printf("\n");
    
    printf("Size of uint64_t: %zu bits\n", 8 * sizeof(uint64_t));
    printf("uint64_t range: %d to %" PRIu64 "\n", 0, UINT64_MAX);
}