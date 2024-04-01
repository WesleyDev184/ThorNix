/**
 * Sets each byte in a block of memory to a specified value.
 *
 * @param b     Pointer to the block of memory to fill.
 * @param c     Value to be set. The value is passed as an int, but the function fills the block of memory using the unsigned char conversion of this value.
 * @param len   Number of bytes to be set to the value.
 *
 * @return      Pointer to the block of memory.
 */
void *memset(void *b, int c, int len){
    unsigned char *p = b;
    while(len > 0){
        *p = c;
        p++;
        len--;
    }
    return b;
}